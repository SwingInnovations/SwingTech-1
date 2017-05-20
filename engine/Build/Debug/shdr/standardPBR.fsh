float DistribGGX(vec3 N, vec3 H, float a){
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;
    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    return nom / denom;
}

float GeomSchlickGGX(float NdotV, float k){
    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + l;
    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float k){
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = GeomSchlickGGX(NdotV, k);
    float ggx2 = GeomSchlickGGX(NdotL, k);
    return ggx1 * ggx2;
}

vec2 Hammersley(int i, int N){
    return vec2( float(i)/float(N), float(bitfieldReverse(uint(i))) * 2.3283064365386963e-10);
}

