#INSERT_HEADER

in vec4 FragPosLightSpace;
uniform sampler2DArray shadowArray;
#include <standard.glinc>
#include <PBR.glinc>
#include <shadow.glinc>

void main(void){
	vec3 Norm = mix(Normal,normalize(TBN* normalize(texture2D(Material.Normal_Tex,TexCoord).xyz*2.0-1.0)),0.1);

	vec3 V = normalize(  _CameraPos - Position );

    float r = clamp(_Roughness,.01, 1.0);

	_GlobalAmbient = texture(_WorldCubeMap,vec3(1,0,0),12).rgb+texture(_WorldCubeMap,vec3(-1,0,0),12).rgb+texture(_WorldCubeMap,vec3(0,1,0),12).rgb

	+texture(_WorldCubeMap,vec3(0,-1,0),12).rgb+texture(_WorldCubeMap,vec3(0,0,1),12).rgb+texture(_WorldCubeMap,vec3(0,0,-1),12).rgb;
	_GlobalAmbient/=6;

	vec3 Spec_Cook_Torrance = Spec_IBL(r,Norm,V,Material.BaseColor);

	///*Ommiting ambient Lighting for now*/vec3 diffuse =mix(baseColor*NdotL*_LightColor,((1- NdotL*_LightColor)*PreFilterEnvMap(1,2* dot(V,Normal)*Normal-V,10)),.4);

	//vec3 diffuse =mix(baseColor*NdotL*_LightColor,((1- NdotL*_LightColor)*PreFilterEnvMap(1,2* dot(V,Normal)*Norm-V,100)),.4);
    float fresnel = pow(1- dot(( Norm),V),r);

   vec3 IBL =  BlendMaterial_IBL(Spec_Cook_Torrance,Material.BaseColor ,fresnel);


 	r = max(_Roughness,.1);

 	for(int i = 0; i < LightCount; i++){
 		if(Light[i].Radius<0){
 		    float bias = max(0.05 * (1.0 - dot(Norm, Light[i].Direction.xyz)), 0.005);
			vec3 Directional_spec = clamp(vec3(Ggx_Dist_old(dot(Norm, normalize(Light[i].Direction.xyz+V)),r)),0.0,1.0);
			vec3 Directional_diff = clamp(vec3(Ggx_Dist_old(dot(Norm, normalize(Light[i].Direction.xyz)),1)),0.0,1.0);
            if(Light[i].Direction.w == 0 || Light[i].Direction.w == -1){
                float shadow = calculateShadow(FragPosLightSpace, shadowArray, Light[i].ShadowIndex, bias);
                color += vec4(BlendMaterial_Directional(Directional_spec,Directional_diff,Material.BaseColor,IBL ,Light[i].Intensity,Light[i].Color, shadow),1);
                //color = vec4((_GlobalAmbient + (1.0 - shadow) * vec3(0.5, 0.5, 0.5)) * Material.BaseColor, 1.0);
            }
		}
	}

}
