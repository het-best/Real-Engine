#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 uResolution;
uniform vec2 uMouse;
uniform float uTime;

#define AUTOCAM
#define SIMPLESC ENE
#define SPECULAR
#define BUMPY
#define SHADOWS
#define pee (acos(0.0)*2.0)

vec3 campos;
vec3 dir;

vec3 rotatex(vec3 v,float anglex)
{
	float t;
	t =   v.y*cos(anglex) - v.z*sin(anglex);
	v.z = v.z*cos(anglex) + v.y*sin(anglex);
	v.y = t;
	return v;
}

vec3 rotcam(vec3 v)
{
	#ifdef AUTOCAM
	float anglex = sin(uTime*0.3)*-0.2+-0.2;
	float angley = uTime*0.2-0.4;
	#else
	float anglex = -( iMouse.y/uResolution.y*0.5-0.05)*pee*1.2; // mouse cam
	float angley = -iMouse.x/uResolution.x*pee*2.0;
	#endif
    
	float t;
	v = rotatex(v,anglex);
	
	t = v.x * cos(angley) - v.z*sin(angley);
	v.z = v.z*cos(angley) + v.x*sin(angley);
	v.x = t;
	return v;
}

int side; // 1 for raytracing outside glass,  -1 for raytracing inside glass

float gTravel;
vec3 gNormal;

float travelMax,travelMin;
vec3 normalMax,normalMin;

// a ray hits a surface surfaceside shows weather it hit from the rear or front of the plane 
void update(float surfaceside,float travel,vec3 normal)
{
	if (surfaceside<0.0)
	{
		if (travelMax<travel)
		{
			travelMax = travel;
			normalMax = normal;
		}
	}
	else
	{
        travelMin = min(travelMin,travel);
	}
}

void hitPlane(vec3 normal,float shift) // check ray-plane intersection. Planes are infinte large
{
	shift += normal.y;         // and shift up from the ground height
	
	float distFromPlane = dot(normal,campos) - shift;
	float travel = -distFromPlane / dot(normal,dir);
	update(dot(normal,dir),travel,normal);
}

void startObj()
{
	travelMax = -1e35;
	travelMin = 1e35;
}

void endObj()
{
//	if (travelMax<travelMin)     // enable this for nonconvex objects
	{
        if (travelMax<travelMin && travelMax>0.0 && travelMax<gTravel)
        {
            gTravel = travelMax;
            gNormal = normalMax;
		}
	}
}

#define plane(a,b,c,d) hitPlane(vec3(a,b,c),-d)

void hitScene();



void bumpit()
{
#ifdef BUMPY
	gNormal.x += sin(campos.x*3.0)*0.02;
	gNormal.y += sin(campos.y*3.0)*0.02;
	gNormal.z += sin(campos.z*3.0)*0.02;
	gNormal = normalize(gNormal);
#endif
}

vec3 lightDir;

vec3 get()
{
    
    float lightintTimePhase = uTime/8.0;
    float sunLightStr = min(1.0,abs(sin(lightintTimePhase*acos(0.0)*2.0)*4.0));
    float angle = float(int(lightintTimePhase))*2.1+2.0;
    lightDir = normalize(vec3(sin(angle),-1.3,cos(angle)));					 

    vec3 color=vec3(0.);
    
    gNormal = vec3(0.0,-1.0,0.0);
    hitScene();
    
    
    campos += dir * gTravel;
    bumpit();
    
    vec3 matColor = vec3(1.0,0.6,0.1);
    vec3 ambient = matColor * mix(vec3(0.3,0.5,0.6),vec3(0.4,0.2,0.0)*sunLightStr,gNormal.y*0.5+0.5);
    vec3 sunlit = matColor * max(dot(gNormal,lightDir),0.0)*sunLightStr;

#ifdef SPECULAR    
    vec3 refdir = reflect(dir,normalize(gNormal));
    float f = dot(refdir,lightDir);
    vec3 refdirplane = normalize(refdir - gNormal*dot(gNormal,refdir));
    vec3 lightdirplane = normalize(lightDir - gNormal*dot(gNormal,lightDir));
    vec3 sidevec = normalize(cross(refdir,gNormal));
    float specy = dot( cross(sidevec,refdir), lightDir);
    float specx = length(cross(refdirplane,lightdirplane)) / dot(refdir,gNormal);
    
    float f2 = length(vec2(specx,specy));
    
    float g = min(1.0 + dot(dir,gNormal),1.0);
    float fresnel = g*g*g*0.95+0.05;
   
    vec3 specular = vec3(1.0,1.0,1.0) * (f>0.5 ? max(exp(f2*-6.0)*40.0,0.0)  : 0.0) * sunLightStr*fresnel;
    sunlit += specular;
  #endif
        
    
    float fog = exp(gTravel*-0.003);
    dir = lightDir;
    gTravel = 1e35;
    #ifdef SHADOWS
    hitScene();
    if (gTravel<=999.) sunlit = vec3(0.);
    #endif
    
    color += mix(vec3(0.1,0.2,0.3), ambient+sunlit,  fog);
    
    return color;
}


	
float func(float x) // the func for HDR (looks better with HDR disabled)
{
	return x/(x+3.0)*3.0;
}
vec3 hdr(vec3 color)
{
    #ifdef HDR
	float pow = length(color);
	color =  color * func(pow)/pow*1.2;
    #endif
    return color;
}

void main()
{
	vec2 uv = gl_FragCoord.xy / uResolution.xy;
	campos = vec3(0,-14,0);
	dir = vec3(uv*2.0-1.0,1);
	dir.y *= -9.0/16.0; // wide screen
	
	dir = normalize(rotcam(dir));
	campos -= rotcam(vec3(0,0,35.0 + 200.0*exp(uTime*-0.8))); // back up from subject
	
	gTravel = 1e35;
	side = 1;
	
		
	gl_FragColor = vec4(hdr(get()),1.0); // add HDR() if you like it
}


void hitScene()
{
startObj();
plane(float(0),float(1),float(0),float(-7));
plane(float(1),float(0),float(0),float(-180));
plane(float(0),float(0),float(-1),float(-180));
plane(float(-1),float(0),float(0),float(-180));
plane(float(0),float(-1),float(0),float(1));
plane(float(0),float(0),float(1),float(-180));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(1),float(0),float(0),float(-31));
plane(float(0),float(-0.624695),float(-0.780869),float(-27.3304));
plane(float(-1),float(0),float(0),float(-31));
plane(float(0),float(-1),float(0),float(-5));
plane(float(0),float(-0.624695),float(0.780869),float(-27.3304));
endObj();

#ifndef SIMPLESCENE
    
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(1),float(0),float(0),float(-53));
plane(float(0),float(0),float(-1),float(-54.5));
plane(float(-1),float(0),float(0),float(37));
plane(float(0),float(-1),float(0),float(-7));
plane(float(0),float(0),float(1),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(1),float(0),float(0),float(-35));
plane(float(0),float(0),float(-1),float(-54.5));
plane(float(-1),float(0),float(0),float(19));
plane(float(0),float(-1),float(0),float(-7));
plane(float(0),float(0),float(1),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(1),float(0),float(0),float(-17));
plane(float(0),float(0),float(-1),float(-54.5));
plane(float(-1),float(0),float(0),float(1));
plane(float(0),float(-1),float(0),float(-7));
plane(float(0),float(0),float(1),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(1),float(0),float(0),float(1));
plane(float(0),float(0),float(-1),float(-54.5));
plane(float(-1),float(0),float(0),float(-17));
plane(float(0),float(-1),float(0),float(-7));
plane(float(0),float(0),float(1),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(1),float(0),float(0),float(19));
plane(float(0),float(0),float(-1),float(-54.5));
plane(float(-1),float(0),float(0),float(-35));
plane(float(0),float(-1),float(0),float(-7));
plane(float(0),float(0),float(1),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(1),float(0),float(0),float(37));
plane(float(0),float(0),float(-1),float(-54.5));
plane(float(-1),float(0),float(0),float(-53));
plane(float(0),float(-1),float(0),float(-7));
plane(float(0),float(0),float(1),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(-4.37114e-008),float(0),float(1),float(-53));
plane(float(1),float(0),float(4.37114e-008),float(-54.5));
plane(float(4.37114e-008),float(0),float(-1),float(37));
plane(float(-0),float(-1),float(0),float(-7));
plane(float(-1),float(0),float(-4.37114e-008),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(-4.37114e-008),float(0),float(1),float(-35));
plane(float(1),float(0),float(4.37114e-008),float(-54.5));
plane(float(4.37114e-008),float(0),float(-1),float(19));
plane(float(-0),float(-1),float(0),float(-7));
plane(float(-1),float(0),float(-4.37114e-008),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(-4.37114e-008),float(0),float(1),float(-17));
plane(float(1),float(0),float(4.37114e-008),float(-54.5));
plane(float(4.37114e-008),float(0),float(-1),float(0.999998));
plane(float(-0),float(-1),float(0),float(-7));
plane(float(-1),float(0),float(-4.37114e-008),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(-4.37114e-008),float(0),float(1),float(0.999998));
plane(float(1),float(0),float(4.37114e-008),float(-54.5));
plane(float(4.37114e-008),float(0),float(-1),float(-17));
plane(float(-0),float(-1),float(0),float(-7));
plane(float(-1),float(0),float(-4.37114e-008),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(-4.37114e-008),float(0),float(1),float(19));
plane(float(1),float(0),float(4.37114e-008),float(-54.5));
plane(float(4.37114e-008),float(0),float(-1),float(-35));
plane(float(-0),float(-1),float(0),float(-7));
plane(float(-1),float(0),float(-4.37114e-008),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(-4.37114e-008),float(0),float(1),float(37));
plane(float(1),float(0),float(4.37114e-008),float(-54.5));
plane(float(4.37114e-008),float(0),float(-1),float(-53));
plane(float(-0),float(-1),float(0),float(-7));
plane(float(-1),float(0),float(-4.37114e-008),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(-1),float(0),float(-8.74228e-008),float(-53));
plane(float(-8.74228e-008),float(0),float(1),float(-54.5));
plane(float(1),float(0),float(8.74228e-008),float(37));
plane(float(0),float(-1),float(-0),float(-7));
plane(float(8.74228e-008),float(0),float(-1),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(-1),float(0),float(-8.74228e-008),float(-35));
plane(float(-8.74228e-008),float(0),float(1),float(-54.5));
plane(float(1),float(0),float(8.74228e-008),float(19));
plane(float(0),float(-1),float(-0),float(-7));
plane(float(8.74228e-008),float(0),float(-1),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(-1),float(0),float(-8.74228e-008),float(-17));
plane(float(-8.74228e-008),float(0),float(1),float(-54.5));
plane(float(1),float(0),float(8.74228e-008),float(1));
plane(float(0),float(-1),float(-0),float(-7));
plane(float(8.74228e-008),float(0),float(-1),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(-1),float(0),float(-8.74228e-008),float(1));
plane(float(-8.74228e-008),float(0),float(1),float(-54.5));
plane(float(1),float(0),float(8.74228e-008),float(-17));
plane(float(0),float(-1),float(-0),float(-7));
plane(float(8.74228e-008),float(0),float(-1),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(-1),float(0),float(-8.74228e-008),float(19));
plane(float(-8.74228e-008),float(0),float(1),float(-54.5));
plane(float(1),float(0),float(8.74228e-008),float(-35));
plane(float(0),float(-1),float(-0),float(-7));
plane(float(8.74228e-008),float(0),float(-1),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-1));
plane(float(-1),float(0),float(-8.74228e-008),float(37));
plane(float(-8.74228e-008),float(0),float(1),float(-54.5));
plane(float(1),float(0),float(8.74228e-008),float(-53));
plane(float(0),float(-1),float(-0),float(-7));
plane(float(8.74228e-008),float(0),float(-1),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-0.999998));
plane(float(-4.64912e-007),float(0),float(-1),float(-53));
plane(float(-1),float(0),float(4.64912e-007),float(-54.5));
plane(float(4.64912e-007),float(0),float(1),float(37));
plane(float(0),float(-1),float(-0),float(-7));
plane(float(1),float(0),float(-4.64912e-007),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-0.999998));
plane(float(-4.64912e-007),float(0),float(-1),float(-35));
plane(float(-1),float(0),float(4.64912e-007),float(-54.5));
plane(float(4.64912e-007),float(0),float(1),float(19));
plane(float(0),float(-1),float(-0),float(-7));
plane(float(1),float(0),float(-4.64912e-007),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-0.999998));
plane(float(-4.64912e-007),float(0),float(-1),float(-17));
plane(float(-1),float(0),float(4.64912e-007),float(-54.5));
plane(float(4.64912e-007),float(0),float(1),float(1));
plane(float(0),float(-1),float(-0),float(-7));
plane(float(1),float(0),float(-4.64912e-007),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-0.999998));
plane(float(-4.64912e-007),float(0),float(-1),float(1));
plane(float(-1),float(0),float(4.64912e-007),float(-54.5));
plane(float(4.64912e-007),float(0),float(1),float(-17));
plane(float(0),float(-1),float(-0),float(-7));
plane(float(1),float(0),float(-4.64912e-007),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-0.999998));
plane(float(-4.64912e-007),float(0),float(-1),float(19));
plane(float(-1),float(0),float(4.64912e-007),float(-54.5));
plane(float(4.64912e-007),float(0),float(1),float(-35));
plane(float(0),float(-1),float(-0),float(-7));
plane(float(1),float(0),float(-4.64912e-007),float(53.5));
endObj();
startObj();
plane(float(0),float(1),float(0),float(-0.999998));
plane(float(-4.64912e-007),float(0),float(-1),float(37));
plane(float(-1),float(0),float(4.64912e-007),float(-54.5));
plane(float(4.64912e-007),float(0),float(1),float(-53));
plane(float(0),float(-1),float(-0),float(-7));
plane(float(1),float(0),float(-4.64912e-007),float(53.5));
endObj();
startObj();
plane(float(0),float(0.707107),float(-0.707107),float(-15.7564));
plane(float(1),float(0),float(0),float(-2.6));
plane(float(0),float(-0.707107),float(-0.707107),float(-23.0774));
plane(float(-1),float(0),float(0),float(-2.6));
plane(float(0),float(-0.707107),float(0.707107),float(15.3564));
plane(float(0),float(0.707107),float(0.707107),float(22.1774));
endObj();
startObj();
plane(float(0.14234),float(0.707107),float(-0.692632),float(-15.7563));
plane(float(0.97953),float(0),float(0.201299),float(-2.6));
plane(float(0.14234),float(-0.707107),float(-0.692632),float(-23.0774));
plane(float(-0.97953),float(0),float(-0.201299),float(-2.6));
plane(float(-0.14234),float(-0.707107),float(0.692632),float(15.3564));
plane(float(-0.14234),float(0.707107),float(0.692632),float(22.1774));
endObj();
startObj();
plane(float(0.278852),float(0.707107),float(-0.649801),float(-15.7564));
plane(float(0.918958),float(0),float(0.394356),float(-2.6));
plane(float(0.278852),float(-0.707107),float(-0.649801),float(-23.0774));
plane(float(-0.918958),float(0),float(-0.394356),float(-2.6));
plane(float(-0.278852),float(-0.707107),float(0.649801),float(15.3564));
plane(float(-0.278852),float(0.707107),float(0.649801),float(22.1774));
endObj();
startObj();
plane(float(0.403948),float(0.707107),float(-0.580367),float(-15.7563));
plane(float(0.820764),float(0),float(0.571268),float(-2.6));
plane(float(0.403948),float(-0.707107),float(-0.580367),float(-23.0774));
plane(float(-0.820764),float(0),float(-0.571268),float(-2.6));
plane(float(-0.403948),float(-0.707107),float(0.580367),float(15.3563));
plane(float(-0.403948),float(0.707107),float(0.580367),float(22.1774));
endObj();
startObj();
plane(float(0.512506),float(0.707107),float(-0.487173),float(-15.7564));
plane(float(0.688967),float(0),float(0.724793),float(-2.6));
plane(float(0.512506),float(-0.707107),float(-0.487173),float(-23.0774));
plane(float(-0.688967),float(0),float(-0.724793),float(-2.6));
plane(float(-0.512506),float(-0.707107),float(0.487173),float(15.3564));
plane(float(-0.512506),float(0.707107),float(0.487173),float(22.1774));
endObj();
startObj();
plane(float(0.600082),float(0.707107),float(-0.374034),float(-15.7564));
plane(float(0.528964),float(0),float(0.848644),float(-2.6));
plane(float(0.600082),float(-0.707107),float(-0.374034),float(-23.0774));
plane(float(-0.528964),float(0),float(-0.848644),float(-2.6));
plane(float(-0.600082),float(-0.707107),float(0.374034),float(15.3564));
plane(float(-0.600082),float(0.707107),float(0.374034),float(22.1774));
endObj();
startObj();
plane(float(0.663091),float(0.707107),float(-0.245582),float(-15.7564));
plane(float(0.347305),float(0),float(0.937752),float(-2.6));
plane(float(0.663091),float(-0.707107),float(-0.245582),float(-23.0774));
plane(float(-0.347305),float(0),float(-0.937752),float(-2.6));
plane(float(-0.663091),float(-0.707107),float(0.245582),float(15.3564));
plane(float(-0.663091),float(0.707107),float(0.245582),float(22.1774));
endObj();
startObj();
plane(float(0.698953),float(0.707107),float(-0.107076),float(-15.7564));
plane(float(0.151428),float(0),float(0.988468),float(-2.6));
plane(float(0.698953),float(-0.707107),float(-0.107076),float(-23.0774));
plane(float(-0.151428),float(0),float(-0.988468),float(-2.6));
plane(float(-0.698953),float(-0.707107),float(0.107076),float(15.3564));
plane(float(-0.698953),float(0.707107),float(0.107076),float(22.1774));
endObj();
startObj();
plane(float(0.706199),float(0.707107),float(0.0358143),float(-15.7564));
plane(float(-0.0506491),float(0),float(0.998717),float(-2.6));
plane(float(0.706199),float(-0.707107),float(0.0358143),float(-23.0774));
plane(float(0.0506491),float(0),float(-0.998717),float(-2.6));
plane(float(-0.706199),float(-0.707107),float(-0.0358143),float(15.3564));
plane(float(-0.706199),float(0.707107),float(-0.0358143),float(22.1774));
endObj();
startObj();
plane(float(0.684534),float(0.707107),float(0.177238),float(-15.7564));
plane(float(-0.250653),float(0),float(0.968077),float(-2.6));
plane(float(0.684534),float(-0.707107),float(0.177238),float(-23.0774));
plane(float(0.250653),float(0),float(-0.968077),float(-2.6));
plane(float(-0.684534),float(-0.707107),float(-0.177238),float(15.3564));
plane(float(-0.684534),float(0.707107),float(-0.177238),float(22.1774));
endObj();
startObj();
plane(float(0.634844),float(0.707107),float(0.311406),float(-15.7564));
plane(float(-0.440394),float(0),float(0.897805),float(-2.6));
plane(float(0.634844),float(-0.707107),float(0.311406),float(-23.0774));
plane(float(0.440394),float(0),float(-0.897805),float(-2.6));
plane(float(-0.634844),float(-0.707107),float(-0.311406),float(15.3564));
plane(float(-0.634844),float(0.707107),float(-0.311406),float(22.1774));
endObj();
startObj();
plane(float(0.559163),float(0.707107),float(0.432824),float(-15.7563));
plane(float(-0.612106),float(0),float(0.790776),float(-2.6));
plane(float(0.559163),float(-0.707107),float(0.432824),float(-23.0774));
plane(float(0.612106),float(0),float(-0.790776),float(-2.6));
plane(float(-0.559163),float(-0.707107),float(-0.432824),float(15.3563));
plane(float(-0.559163),float(0.707107),float(-0.432824),float(22.1774));
endObj();
startObj();
plane(float(0.46059),float(0.707107),float(0.536523),float(-15.7564));
plane(float(-0.758758),float(0),float(0.651373),float(-2.6));
plane(float(0.46059),float(-0.707107),float(0.536523),float(-23.0774));
plane(float(0.758758),float(0),float(-0.651373),float(-2.6));
plane(float(-0.46059),float(-0.707107),float(-0.536523),float(15.3564));
plane(float(-0.46059),float(0.707107),float(-0.536523),float(22.1774));
endObj();
startObj();
plane(float(0.34316),float(0.707107),float(0.618256),float(-15.7563));
plane(float(-0.874347),float(0),float(0.485302),float(-2.6));
plane(float(0.34316),float(-0.707107),float(0.618256),float(-23.0774));
plane(float(0.874347),float(0),float(-0.485302),float(-2.6));
plane(float(-0.34316),float(-0.707107),float(-0.618256),float(15.3563));
plane(float(-0.34316),float(0.707107),float(-0.618256),float(22.1774));
endObj();
startObj();
plane(float(0.211682),float(0.707107),float(0.674679),float(-15.7564));
plane(float(-0.954139),float(0),float(0.299363),float(-2.6));
plane(float(0.211681),float(-0.707107),float(0.674678),float(-23.0774));
plane(float(0.954139),float(0),float(-0.299363),float(-2.6));
plane(float(-0.211682),float(-0.707107),float(-0.674679),float(15.3564));
plane(float(-0.211681),float(0.707107),float(-0.674678),float(22.1774));
endObj();
startObj();
plane(float(0.0715369),float(0.707107),float(0.703479),float(-15.7563));
plane(float(-0.994869),float(0),float(0.101168),float(-2.6));
plane(float(0.0715369),float(-0.707107),float(0.703479),float(-23.0774));
plane(float(0.994869),float(0),float(-0.101168),float(-2.6));
plane(float(-0.0715369),float(-0.707107),float(-0.703479),float(15.3563));
plane(float(-0.0715369),float(0.707107),float(-0.703479),float(22.1774));
endObj();
startObj();
plane(float(-0.0715367),float(0.707107),float(0.703479),float(-15.7563));
plane(float(-0.994869),float(0),float(-0.101168),float(-2.6));
plane(float(-0.0715367),float(-0.707107),float(0.703479),float(-23.0774));
plane(float(0.994869),float(0),float(0.101168),float(-2.6));
plane(float(0.0715367),float(-0.707107),float(-0.703479),float(15.3563));
plane(float(0.0715367),float(0.707107),float(-0.703479),float(22.1774));
endObj();
startObj();
plane(float(-0.211682),float(0.707107),float(0.674678),float(-15.7564));
plane(float(-0.954139),float(0),float(-0.299363),float(-2.6));
plane(float(-0.211682),float(-0.707107),float(0.674678),float(-23.0774));
plane(float(0.954139),float(0),float(0.299363),float(-2.6));
plane(float(0.211682),float(-0.707107),float(-0.674678),float(15.3564));
plane(float(0.211682),float(0.707107),float(-0.674678),float(22.1774));
endObj();
startObj();
plane(float(-0.34316),float(0.707107),float(0.618257),float(-15.7564));
plane(float(-0.874347),float(0),float(-0.485302),float(-2.6));
plane(float(-0.34316),float(-0.707107),float(0.618256),float(-23.0774));
plane(float(0.874347),float(0),float(0.485302),float(-2.6));
plane(float(0.34316),float(-0.707107),float(-0.618257),float(15.3564));
plane(float(0.34316),float(0.707107),float(-0.618256),float(22.1774));
endObj();
startObj();
plane(float(-0.46059),float(0.707107),float(0.536523),float(-15.7564));
plane(float(-0.758758),float(0),float(-0.651372),float(-2.6));
plane(float(-0.46059),float(-0.707107),float(0.536523),float(-23.0774));
plane(float(0.758758),float(0),float(0.651372),float(-2.6));
plane(float(0.46059),float(-0.707107),float(-0.536523),float(15.3564));
plane(float(0.46059),float(0.707107),float(-0.536523),float(22.1774));
endObj();
startObj();
plane(float(-0.559163),float(0.707107),float(0.432824),float(-15.7563));
plane(float(-0.612106),float(0),float(-0.790776),float(-2.6));
plane(float(-0.559163),float(-0.707107),float(0.432824),float(-23.0774));
plane(float(0.612106),float(0),float(0.790776),float(-2.6));
plane(float(0.559163),float(-0.707107),float(-0.432824),float(15.3563));
plane(float(0.559163),float(0.707107),float(-0.432824),float(22.1774));
endObj();
startObj();
plane(float(-0.634844),float(0.707107),float(0.311406),float(-15.7564));
plane(float(-0.440394),float(0),float(-0.897804),float(-2.6));
plane(float(-0.634844),float(-0.707107),float(0.311406),float(-23.0774));
plane(float(0.440394),float(0),float(0.897804),float(-2.6));
plane(float(0.634844),float(-0.707107),float(-0.311406),float(15.3564));
plane(float(0.634844),float(0.707107),float(-0.311406),float(22.1774));
endObj();
startObj();
plane(float(-0.684534),float(0.707107),float(0.177238),float(-15.7564));
plane(float(-0.250653),float(0),float(-0.968077),float(-2.6));
plane(float(-0.684534),float(-0.707107),float(0.177238),float(-23.0774));
plane(float(0.250653),float(0),float(0.968077),float(-2.6));
plane(float(0.684534),float(-0.707107),float(-0.177238),float(15.3564));
plane(float(0.684534),float(0.707107),float(-0.177238),float(22.1774));
endObj();
startObj();
plane(float(-0.706199),float(0.707107),float(0.0358149),float(-15.7564));
plane(float(-0.0506499),float(0),float(-0.998717),float(-2.6));
plane(float(-0.706199),float(-0.707107),float(0.0358149),float(-23.0774));
plane(float(0.0506499),float(0),float(0.998717),float(-2.6));
plane(float(0.706199),float(-0.707107),float(-0.0358149),float(15.3564));
plane(float(0.706199),float(0.707107),float(-0.0358149),float(22.1774));
endObj();
startObj();
plane(float(-0.698953),float(0.707107),float(-0.107075),float(-15.7564));
plane(float(0.151428),float(0),float(-0.988468),float(-2.6));
plane(float(-0.698953),float(-0.707107),float(-0.107075),float(-23.0774));
plane(float(-0.151428),float(0),float(0.988468),float(-2.6));
plane(float(0.698953),float(-0.707107),float(0.107075),float(15.3564));
plane(float(0.698953),float(0.707107),float(0.107075),float(22.1774));
endObj();
startObj();
plane(float(-0.663091),float(0.707107),float(-0.245582),float(-15.7564));
plane(float(0.347305),float(0),float(-0.937752),float(-2.6));
plane(float(-0.663091),float(-0.707107),float(-0.245582),float(-23.0774));
plane(float(-0.347305),float(0),float(0.937752),float(-2.6));
plane(float(0.663091),float(-0.707107),float(0.245582),float(15.3564));
plane(float(0.663091),float(0.707107),float(0.245582),float(22.1774));
endObj();
startObj();
plane(float(-0.600082),float(0.707107),float(-0.374034),float(-15.7564));
plane(float(0.528964),float(0),float(-0.848644),float(-2.6));
plane(float(-0.600082),float(-0.707107),float(-0.374034),float(-23.0774));
plane(float(-0.528964),float(0),float(0.848644),float(-2.6));
plane(float(0.600082),float(-0.707107),float(0.374034),float(15.3564));
plane(float(0.600082),float(0.707107),float(0.374034),float(22.1774));
endObj();
startObj();
plane(float(-0.512506),float(0.707107),float(-0.487173),float(-15.7564));
plane(float(0.688967),float(0),float(-0.724793),float(-2.6));
plane(float(-0.512506),float(-0.707107),float(-0.487173),float(-23.0774));
plane(float(-0.688967),float(0),float(0.724793),float(-2.6));
plane(float(0.512506),float(-0.707107),float(0.487173),float(15.3564));
plane(float(0.512506),float(0.707107),float(0.487173),float(22.1774));
endObj();
startObj();
plane(float(-0.403947),float(0.707107),float(-0.580368),float(-15.7564));
plane(float(0.820764),float(0),float(-0.571268),float(-2.6));
plane(float(-0.403947),float(-0.707107),float(-0.580368),float(-23.0774));
plane(float(-0.820764),float(0),float(0.571268),float(-2.6));
plane(float(0.403947),float(-0.707107),float(0.580368),float(15.3564));
plane(float(0.403947),float(0.707107),float(0.580368),float(22.1774));
endObj();
startObj();
plane(float(-0.278852),float(0.707107),float(-0.649801),float(-15.7564));
plane(float(0.918958),float(0),float(-0.394356),float(-2.6));
plane(float(-0.278852),float(-0.707107),float(-0.649801),float(-23.0774));
plane(float(-0.918958),float(0),float(0.394356),float(-2.6));
plane(float(0.278852),float(-0.707107),float(0.649801),float(15.3564));
plane(float(0.278852),float(0.707107),float(0.649801),float(22.1774));
endObj();
startObj();
plane(float(-0.14234),float(0.707107),float(-0.692632),float(-15.7564));
plane(float(0.97953),float(0),float(-0.201299),float(-2.6));
plane(float(-0.14234),float(-0.707107),float(-0.692632),float(-23.0774));
plane(float(-0.97953),float(0),float(0.201299),float(-2.6));
plane(float(0.14234),float(-0.707107),float(0.692632),float(15.3564));
plane(float(0.14234),float(0.707107),float(0.692632),float(22.1774));
endObj();
    
    #endif
    
startObj();
plane(float(0.383867),float(0.920614),float(-0.0715337),float(13.6711));
plane(float(0.888832),float(-0.389385),float(-0.241572),float(-7.57762));
plane(float(-0.250248),float(0.0291498),float(-0.967743),float(3.81964));
plane(float(-0.888832),float(0.389385),float(0.241572),float(1.97762));
plane(float(-0.383867),float(-0.920614),float(0.0715337),float(-18.0711));
plane(float(0.250248),float(-0.0291498),float(0.967743),float(-7.81964));
endObj();
startObj();
plane(float(0.410012),float(0.900413),float(-0.14542),float(18.3884));
plane(float(0.838925),float(-0.434866),float(-0.327257),float(-7.87907));
plane(float(-0.357905),float(0.0121831),float(-0.933679),float(3.68534));
plane(float(-0.838925),float(0.434866),float(0.327257),float(2.47907));
plane(float(-0.410012),float(-0.900413),float(0.14542),float(-22.7884));
plane(float(0.357905),float(-0.0121831),float(0.933679),float(-6.68534));
endObj();
startObj();
plane(float(0.0244033),float(0.939602),float(-0.341399),float(24.3099));
plane(float(0.844816),float(-0.201969),float(-0.495474),float(0.19967));
plane(float(-0.534501),float(-0.276328),float(-0.798719),float(-4.15355));
plane(float(-0.844816),float(0.201969),float(0.495474),float(-2.59967));
plane(float(-0.0244033),float(-0.939602),float(0.341399),float(-27.3099));
plane(float(0.534501),float(0.276328),float(0.798719),float(1.75355));
endObj();
startObj();
plane(float(0.317596),float(0.945882),float(0.0666309),float(6.54595));
plane(float(0.676376),float(-0.176735),float(-0.715038),float(2.07443));
plane(float(-0.664566),float(0.272161),float(-0.695903),float(0.841951));
plane(float(-0.676376),float(0.176735),float(0.715038),float(-4.47443));
plane(float(-0.317596),float(-0.945882),float(-0.0666309),float(-7.94595));
plane(float(0.664566),float(-0.272161),float(0.695903),float(-4.84195));
endObj();
startObj();
plane(float(0.2856),float(0.864013),float(0.414626),float(5.54048));
plane(float(0.783863),float(0.0383015),float(-0.619751),float(3.89471));
plane(float(-0.551354),float(0.502011),float(-0.666329),float(4.75963));
plane(float(-0.783863),float(-0.0383015),float(0.619751),float(-5.89471));
plane(float(-0.2856),float(-0.864013),float(-0.414626),float(-10.1405));
plane(float(0.551354),float(-0.502011),float(0.666329),float(-6.75963));
endObj();
startObj();
plane(float(-0.571276),float(0.468744),float(-0.673739),float(4.78791));
plane(float(0.775637),float(0.0399012),float(-0.629917),float(3.75132));
plane(float(-0.268386),float(-0.882433),float(-0.38637),float(-11.7256));
plane(float(-0.775637),float(-0.0399012),float(0.629917),float(-6.15132));
plane(float(0.571276),float(-0.468744),float(0.673739),float(-10.7879));
plane(float(0.268386),float(0.882433),float(0.38637),float(9.32558));
endObj();
startObj();
plane(float(0.308545),float(0.928811),float(-0.205206),float(6.03705));
plane(float(0.918407),float(-0.347056),float(-0.18995),float(-7.52246));
plane(float(-0.247645),float(-0.129855),float(-0.960109),float(6.22725));
plane(float(-0.918407),float(0.347056),float(0.18995),float(5.12246));
plane(float(-0.308545),float(-0.928811),float(0.205206),float(-7.43705));
plane(float(0.247645),float(0.129855),float(0.960109),float(-10.2273));
endObj();
startObj();
plane(float(0.431007),float(0.77232),float(0.466642),float(-0.784515));
plane(float(0.899674),float(-0.40759),float(-0.156386),float(-8.04544));
plane(float(0.0694185),float(0.48723),float(-0.870511),float(10.6768));
plane(float(-0.899674),float(0.40759),float(0.156386),float(6.04544));
plane(float(-0.431007),float(-0.77232),float(-0.466642),float(-3.81548));
plane(float(-0.0694185),float(-0.48723),float(0.870511),float(-12.6768));
endObj();
startObj();
plane(float(0.430124),float(0.77742),float(0.458924),float(3.62615));
plane(float(0.900341),float(-0.406668),float(-0.154942),float(-8.18314));
plane(float(0.066175),float(0.479833),float(-0.874861),float(10.4767));
plane(float(-0.900341),float(0.406668),float(0.154942),float(5.78314));
plane(float(-0.430124),float(-0.77742),float(-0.458924),float(-9.62614));
plane(float(-0.066175),float(-0.479833),float(0.874861),float(-12.8767));
endObj();
startObj();
plane(float(0.976008),float(0.210468),float(0.0557845),float(9.03892));
plane(float(0.173523),float(-0.906622),float(0.384613),float(-21.4466));
plane(float(0.131524),float(-0.365706),float(-0.921391),float(-1.29409));
plane(float(-0.173523),float(0.906622),float(-0.384613),float(17.6466));
plane(float(-0.976008),float(-0.210468),float(-0.0557845),float(-10.6389));
plane(float(-0.131524),float(0.365706),float(0.921391),float(-0.905906));
endObj();
startObj();
plane(float(0.961897),float(0.266605),float(0.0606273),float(10.5645));
plane(float(0.213293),float(-0.870442),float(0.443663),float(-17.4709));
plane(float(0.171056),float(-0.413827),float(-0.89414),float(-1.59577));
plane(float(-0.213293),float(0.870442),float(-0.443663),float(13.6709));
plane(float(-0.961897),float(-0.266605),float(-0.0606273),float(-11.9645));
plane(float(-0.171056),float(0.413827),float(0.89414),float(-0.00423229));
endObj();
startObj();
plane(float(0.960554),float(0.270338),float(0.0652159),float(11.1644));
plane(float(0.214924),float(-0.870481),float(0.4428),float(-14.306));
plane(float(0.176475),float(-0.411317),float(-0.894246),float(-2.16547));
plane(float(-0.214924),float(0.870481),float(-0.4428),float(11.506));
plane(float(-0.960554),float(-0.270338),float(-0.0652159),float(-11.7644));
plane(float(-0.176475),float(0.411317),float(0.894246),float(-0.0345296));
endObj();
startObj();
plane(float(-0.624082),float(0.264051),float(-0.73539),float(9.30376));
plane(float(-0.276092),float(-0.954977),float(-0.108594),float(-25.9317));
plane(float(-0.730955),float(0.135264),float(0.668887),float(-1.63207));
plane(float(0.276092),float(0.954977),float(0.108594),float(22.1317));
plane(float(0.624082),float(-0.264051),float(0.73539),float(-10.9038));
plane(float(0.730955),float(-0.135264),float(-0.668887),float(-0.567926));
endObj();
startObj();
plane(float(-0.682675),float(0.247512),float(-0.687526),float(8.86892));
plane(float(-0.730557),float(-0.211166),float(0.649381),float(-13.1815));
plane(float(0.0155472),float(0.945593),float(0.32498),float(23.4904));
plane(float(0.730557),float(0.211166),float(-0.649381),float(9.38148));
plane(float(0.682675),float(-0.247512),float(0.687526),float(-10.2689));
plane(float(-0.0155472),float(-0.945593),float(-0.32498),float(-25.0904));
endObj();
startObj();
plane(float(-0.873077),float(0.112964),float(-0.474316),float(3.26787));
plane(float(-0.487496),float(-0.220571),float(0.844805),float(-16.0544));
plane(float(-0.00918784),float(0.968807),float(0.247645),float(24.6254));
plane(float(0.487496),float(0.220571),float(-0.844805),float(13.2544));
plane(float(0.873077),float(-0.112964),float(0.474316),float(-3.86787));
plane(float(0.00918784),float(-0.968807),float(-0.247645),float(-26.8254));
endObj();
}