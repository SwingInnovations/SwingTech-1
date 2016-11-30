#version 400 core


#include <standard.glinc>

#include <PBR.glinc>




void main(void){


	vec3 Norm =  normalize(TBN* normalize(texture2D(Material.Normal_Tex,TexCoord).xyz*2.0-1.0));

	vec3 V = normalize(  _CameraPos - Position );

    float r = clamp(_Roughness,.01, 1.0);

	_GlobalAmbient = texture(_WorldCubeMap,vec3(1,0,0),12).rgb+texture(_WorldCubeMap,vec3(-1,0,0),12).rgb+texture(_WorldCubeMap,vec3(0,1,0),12).rgb

	+texture(_WorldCubeMap,vec3(0,-1,0),12).rgb+texture(_WorldCubeMap,vec3(0,0,1),12).rgb+texture(_WorldCubeMap,vec3(0,0,-1),12).rgb;
	_GlobalAmbient/=6;

	vec3 Spec_Cook_Torrance =Spec_IBL(r,Norm,V,Material.BaseColor);

	///*Ommiting ambient Lighting for now*/vec3 diffuse =mix(baseColor*NdotL*_LightColor,((1- NdotL*_LightColor)*PreFilterEnvMap(1,2* dot(V,Normal)*Normal-V,10)),.4);

	//vec3 diffuse =mix(baseColor*NdotL*_LightColor,((1- NdotL*_LightColor)*PreFilterEnvMap(1,2* dot(V,Normal)*Norm-V,100)),.4);
    float fresnel = pow(1- dot(( Norm),V),r);

   vec3 IBL =  BlendMaterial_IBL(Spec_Cook_Torrance,Material.BaseColor ,fresnel);


 	r = max(_Roughness,.1);


 	for(int i = 0; i < 2; i++){
 		if(Light[i].Radius<0){
			vec3 Directional_spec = clamp(vec3(Ggx_Dist_old(dot(Norm, normalize(Light[i].Direction+V)),r)),0.0,1.0);
			vec3 Directional_diff = clamp(vec3(Ggx_Dist_old(dot(Norm, normalize(Light[i].Direction)),1)),0.0,1.0);

			color += vec4(BlendMaterial_Directional(Directional_spec,Directional_diff,Material.BaseColor,IBL ,Light[i].Intensity,Light[i].Color),1);
		}
	}

}
