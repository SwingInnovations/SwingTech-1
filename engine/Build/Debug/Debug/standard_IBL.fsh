#version 400 core

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
in mat3 TBN;
in vec4 FragPosLightSpace;


uniform samplerCube _WorldCubeMap;
uniform vec3 _GlobalAmbient;
uniform vec3 _CameraPos;
uniform vec3 _LightPosition;

 uniform float _Metallic;
 uniform float _Roughness;


struct STMaterial
{
	vec3 BaseColor;
	sampler2D Diffuse_Tex;
	sampler2D Normal_Tex;
};
uniform sampler2D shadowMap;

uniform STMaterial Material;

out vec4 color;

const float PI = 3.14159265359;

float Schlick_Geometry_Hack_Partial( float NdotV, float r){

	float k =(r*r)*2;
	return   (NdotV*(1-k)+k);
}

float G_Smith(float NdotL, float NdotV, float r){

	
	return Schlick_Geometry_Hack_Partial(NdotL,r)*Schlick_Geometry_Hack_Partial(NdotV,r);
}



// Hammersley function (return random low-discrepency points)
vec2 Hammersley(int i, int N)
{
  return vec2(
    float(i) / float(N),
    float(bitfieldReverse(uint(i))) * 2.3283064365386963e-10
  );
}


vec3 ISample_Ggx(vec2 Xi, float R, vec3 N)
{

	float a = R*R;

	float Phi = 2 * PI * Xi.x;
	float CosTheta = sqrt(( 1 - Xi.y ) / ( 1 + ( a * a -1 ) * Xi.y ) );
	float SinTheta = sqrt( 1 - CosTheta * CosTheta );

	vec3 H = vec3(
			SinTheta * cos( Phi ),
			SinTheta * sin( Phi ),
			CosTheta);

	vec3 up = abs(N.z) < .999 ? vec3(0,0,1) : vec3(1,0,0);
	vec3 tanx = normalize( cross( up , N ) );
	vec3 tany = normalize( cross( N , tanx ) );

	return tanx * H.x + tany * H.y + N * H.z;

}


vec3 PreFilterEnvMap( float roughness, vec3 R, int SampleCount){

	vec3 N= R;
	vec3 V= R;

	vec3 fliteredColor = vec3(0);

	

	float w=0;

	for( int i =0; i< SampleCount; i++ )
	{
		vec2 Xi = Hammersley( i, SampleCount );

		vec3 H = ISample_Ggx( Xi, roughness, N );
		vec3 L = 2 * dot( V , H ) * H - V;

		float NdotL = clamp( dot( N , L ) , 0 , 1 );
		
	
		if ( NdotL >= 0 ){

			fliteredColor += texture(_WorldCubeMap, L, roughness*4).xyz*NdotL;
			w+=NdotL;

		}
	}

	return (fliteredColor / w);

}

vec3 PreFilterEnvMap( float roughness, vec3 R){

	return PreFilterEnvMap( roughness, R, int(clamp(70.0*(roughness),40,70)));
}



vec2 IntegrateBRDF( float R, float NdotV){

	vec3 V;
	V.x= sqrt(1.0f - NdotV *NdotV);
	V.y =0;
	V.z = NdotV;

	float A = 0;
	float B = 0;


	int SampleCount = 1;
	float w=0;

	for( int i =0; i< SampleCount; i++ )
	{
		vec2 Xi = Hammersley( i, SampleCount );

		vec3 H = ISample_Ggx( Xi, R, Normal );
		vec3 L = 2 * dot( V , H ) * H - V;

		
		float NdotL = clamp(L.z , 0 , 1 );
		float NdotH = clamp(  H.z  , 0 , 1 );
		float VdotH = clamp( dot( V , H ) , 0 , 1 );

		
		if ( NdotL > 0 ){
			
			float G_Vis =G_Smith( NdotL, NdotV, R )* VdotH / (NdotH * NdotV);

			float Fc = pow( 1 - dot( Normal , V ), 5 );
 			

			A+=(1 - Fc) * G_Vis;

			B+= Fc * G_Vis;
			w+=G_Vis;
		}
	}

	return vec2(A,B)/SampleCount;

}

vec2 IntegrateBRDFMobile( float R, float NdotV){

	 vec4 c0 = vec4( -1, -0.0275, -0.572, 0.022 );
	 vec4 c1 = vec4( 1, 0.0425, 1.04, -0.04 );
	vec4 r = R * c0 + c1;
	float a004 = min( r.x * r.x, exp2( -9.28 * NdotV ) ) * r.x + r.y;
	vec2 AB = vec2( -1.04, 1.04 ) * a004 + r.zw;
	return AB;
}

vec3 Spec_IBL( float roughness, vec3 N, vec3 V, vec3 baseColor){
	float NdotV = clamp (dot(N,V),0,1);
	vec3 R = 2* dot(V,N)*N-V;


	vec3 PreFilteredColor = PreFilterEnvMap(roughness,R);
	vec2 BRDF = IntegrateBRDFMobile(roughness, NdotV);

	return  PreFilteredColor* (baseColor*  BRDF.x + BRDF.y);
}

float CalculateShadow(vec4 fragPos){
    vec3 projCoord = fragPos.xyz / fragPos.w;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    projCoord = projCoord * 0.5 + 0.5;
    vec2 texCoord = vec2(projCoord.x, projCoord.y);
    float closestDepth = texture(shadowMap, texCoord).r;
    float currentDepth = projCoord.z;
    float bias = max( 0.05 * (1.0 - dot(Normal, _LightPosition)), 0.005);
    //float shadow = currentDepth - 0.008f > closestDepth ? 1.0 : 0.0;
    float shadow = 0;
    for(int x = -1; x <= 1; x++){
        for(int y = -1; y <= 1; y++){
            float pcfDepth = texture(shadowMap, texCoord + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    return shadow / 11.0;
}

vec3 BlendMaterial(vec3 Spec, vec3 Diff, vec3 Base,float fresnel){
	
	vec3 dialectric = Base* texture2D(Material.Diffuse_Tex,TexCoord).rgb+fresnel*Spec*.6;
	vec3 metal = Base*Spec;

	return mix(dialectric,metal,_Metallic);
}



void main(void){

		
	vec3 Norm = (TBN* (texture2D(Material.Normal_Tex,TexCoord).xyz*2-1));
	
	vec3 V = normalize(  _CameraPos - Position );

    float roughness = clamp(_Roughness,.01, 1.0);

	vec3 Spec_Cook_Torrance =Spec_IBL(roughness,Norm,V,Material.BaseColor);

	///*Ommiting ambient Lighting for now*/vec3 diffuse =mix(baseColor*NdotL*_LightColor,((1- NdotL*_LightColor)*PreFilterEnvMap(1,2* dot(V,Normal)*Normal-V,10)),.4);
	vec3 diffuse =Material.BaseColor/PI;
	//vec3 diffuse =mix(baseColor*NdotL*_LightColor,((1- NdotL*_LightColor)*PreFilterEnvMap(1,2* dot(V,Normal)*Norm-V,100)),.4);
    float fresnel = pow(1- dot(( Norm),V),1);
    float s = CalculateShadow(FragPosLightSpace);
    vec3 col = BlendMaterial(Spec_Cook_Torrance,diffuse,Material.BaseColor ,fresnel);
    vec3 amb = 0.15 * col;
    //color =  vec4(amb + ((1.0 - s) * col),1);
    color = vec4(1.0, 0.0, 0.0, 1.0);
}



