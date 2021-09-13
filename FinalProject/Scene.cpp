//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"

const int LUTSize = 1024;
float LUT[LUTSize] = {
	0.0f, 0.00195631f, 0.00391517f, 0.0058766f, 0.00784058f,
	0.00980714f, 0.0117763f, 0.013748f, 0.0157223f, 0.0176992f,
	0.0196787f, 0.0216608f, 0.0236456f, 0.0256329f, 0.0276229f,
	0.0296155f, 0.0316107f, 0.0336086f, 0.0356091f, 0.0376123f,
	0.0396182f, 0.0416267f, 0.0436379f, 0.0456518f, 0.0476683f,
	0.0496876f, 0.0517095f, 0.0537342f, 0.0557616f, 0.0577916f,
	0.0598245f, 0.06186f, 0.0638983f, 0.0659393f, 0.0679831f,
	0.0700296f, 0.0720789f, 0.074131f, 0.0761858f, 0.0782434f,
	0.0803039f, 0.0823671f, 0.0844331f, 0.0865019f, 0.0885736f,
	0.090648f, 0.0927253f, 0.0948054f, 0.0968884f, 0.0989742f,
	0.101063f, 0.103154f, 0.105249f, 0.107346f, 0.109446f,
	0.111549f, 0.113655f, 0.115764f, 0.117876f, 0.119991f,
	0.122108f, 0.124229f, 0.126352f, 0.128479f, 0.130608f,
	0.132741f, 0.134876f, 0.137014f, 0.139155f, 0.1413f,
	0.143447f, 0.145597f, 0.147751f, 0.149907f, 0.152066f,
	0.154229f, 0.156394f, 0.158562f, 0.160734f, 0.162909f,
	0.165086f, 0.167267f, 0.169451f, 0.171638f, 0.173828f,
	0.176021f, 0.178217f, 0.180416f, 0.182619f, 0.184824f,
	0.187033f, 0.189245f, 0.19146f, 0.193679f, 0.1959f,
	0.198125f, 0.200352f, 0.202583f, 0.204818f, 0.207055f,
	0.209296f, 0.21154f, 0.213787f, 0.216037f, 0.218291f,
	0.220548f, 0.222808f, 0.225072f, 0.227339f, 0.229609f,
	0.231882f, 0.234159f, 0.236439f, 0.238722f, 0.241009f,
	0.243299f, 0.245593f, 0.247889f, 0.25019f, 0.252493f,
	0.2548f, 0.257111f, 0.259424f, 0.261742f, 0.264062f,
	0.266386f, 0.268714f, 0.271045f, 0.273379f, 0.275717f,
	0.278058f, 0.280403f, 0.282752f, 0.285104f, 0.287459f,
	0.289818f, 0.29218f, 0.294546f, 0.296916f, 0.299289f,
	0.301666f, 0.304046f, 0.30643f, 0.308818f, 0.311209f,
	0.313603f, 0.316002f, 0.318404f, 0.320809f, 0.323219f,
	0.325632f, 0.328048f, 0.330469f, 0.332893f, 0.33532f,
	0.337752f, 0.340187f, 0.342626f, 0.345068f, 0.347515f,
	0.349965f, 0.352419f, 0.354877f, 0.357338f, 0.359804f,
	0.362273f, 0.364746f, 0.367223f, 0.369703f, 0.372188f,
	0.374676f, 0.377168f, 0.379665f, 0.382165f, 0.384669f,
	0.387176f, 0.389688f, 0.392204f, 0.394724f, 0.397247f,
	0.399775f, 0.402307f, 0.404842f, 0.407382f, 0.409925f,
	0.412473f, 0.415025f, 0.417581f, 0.42014f, 0.422704f,
	0.425272f, 0.427844f, 0.43042f, 0.433001f, 0.435585f,
	0.438174f, 0.440766f, 0.443363f, 0.445964f, 0.448569f,
	0.451179f, 0.453792f, 0.45641f, 0.459032f, 0.461659f,
	0.464289f, 0.466924f, 0.469563f, 0.472207f, 0.474854f,
	0.477506f, 0.480163f, 0.482823f, 0.485488f, 0.488158f,
	0.490831f, 0.49351f, 0.496192f, 0.498879f, 0.50157f,
	0.504266f, 0.506966f, 0.509671f, 0.51238f, 0.515094f,
	0.517812f, 0.520535f, 0.523262f, 0.525994f, 0.52873f,
	0.531471f, 0.534217f, 0.536967f, 0.539721f, 0.542481f,
	0.545244f, 0.548013f, 0.550786f, 0.553564f, 0.556347f,
	0.559134f, 0.561926f, 0.564722f, 0.567524f, 0.57033f,
	0.573141f, 0.575957f, 0.578777f, 0.581602f, 0.584433f,
	0.587267f, 0.590107f, 0.592952f, 0.595801f, 0.598656f,
	0.601515f, 0.60438f, 0.607249f, 0.610123f, 0.613002f,
	0.615886f, 0.618775f, 0.621669f, 0.624568f, 0.627472f,
	0.630382f, 0.633296f, 0.636215f, 0.63914f, 0.642069f,
	0.645004f, 0.647944f, 0.650889f, 0.653839f, 0.656794f,
	0.659755f, 0.662721f, 0.665692f, 0.668668f, 0.671649f,
	0.674636f, 0.677628f, 0.680626f, 0.683628f, 0.686636f,
	0.68965f, 0.692669f, 0.695693f, 0.698723f, 0.701758f,
	0.704798f, 0.707844f, 0.710896f, 0.713953f, 0.717015f,
	0.720083f, 0.723157f, 0.726236f, 0.729321f, 0.732411f,
	0.735507f, 0.738608f, 0.741715f, 0.744828f, 0.747947f,
	0.751071f, 0.754201f, 0.757337f, 0.760478f, 0.763625f,
	0.766778f, 0.769937f, 0.773102f, 0.776272f, 0.779449f,
	0.782631f, 0.785819f, 0.789013f, 0.792213f, 0.795419f,
	0.798631f, 0.801849f, 0.805073f, 0.808303f, 0.811539f,
	0.814781f, 0.818029f, 0.821284f, 0.824544f, 0.827811f,
	0.831083f, 0.834362f, 0.837647f, 0.840939f, 0.844236f,
	0.84754f, 0.85085f, 0.854167f, 0.85749f, 0.860819f,
	0.864154f, 0.867496f, 0.870844f, 0.874199f, 0.87756f,
	0.880928f, 0.884302f, 0.887683f, 0.89107f, 0.894464f,
	0.897864f, 0.901271f, 0.904685f, 0.908105f, 0.911532f,
	0.914966f, 0.918406f, 0.921853f, 0.925307f, 0.928767f,
	0.932235f, 0.935709f, 0.93919f, 0.942678f, 0.946173f,
	0.949674f, 0.953183f, 0.956698f, 0.960221f, 0.96375f,
	0.967287f, 0.970831f, 0.974381f, 0.977939f, 0.981504f,
	0.985076f, 0.988656f, 0.992242f, 0.995836f, 0.999437f,
	1.00304f, 1.00666f, 1.01028f, 1.01391f, 1.01755f,
	1.0212f, 1.02485f, 1.02851f, 1.03218f, 1.03585f,
	1.03953f, 1.04322f, 1.04692f, 1.05062f, 1.05434f,
	1.05806f, 1.06179f, 1.06552f, 1.06926f, 1.07302f,
	1.07677f, 1.08054f, 1.08432f, 1.0881f, 1.09189f,
	1.09569f, 1.09949f, 1.10331f, 1.10713f, 1.11096f,
	1.1148f, 1.11865f, 1.1225f, 1.12636f, 1.13023f,
	1.13411f, 1.138f, 1.1419f, 1.1458f, 1.14971f,
	1.15363f, 1.15756f, 1.1615f, 1.16544f, 1.1694f,
	1.17336f, 1.17733f, 1.18131f, 1.1853f, 1.1893f,
	1.1933f, 1.19732f, 1.20134f, 1.20537f, 1.20942f,
	1.21346f, 1.21752f, 1.22159f, 1.22567f, 1.22975f,
	1.23385f, 1.23795f, 1.24206f, 1.24618f, 1.25031f,
	1.25445f, 1.2586f, 1.26276f, 1.26693f, 1.2711f,
	1.27529f, 1.27949f, 1.28369f, 1.2879f, 1.29213f,
	1.29636f, 1.3006f, 1.30486f, 1.30912f, 1.31339f,
	1.31767f, 1.32196f, 1.32626f, 1.33057f, 1.33489f,
	1.33922f, 1.34356f, 1.34791f, 1.35227f, 1.35664f,
	1.36102f, 1.36541f, 1.36981f, 1.37422f, 1.37864f,
	1.38307f, 1.38752f, 1.39197f, 1.39643f, 1.4009f,
	1.40538f, 1.40988f, 1.41438f, 1.41889f, 1.42342f,
	1.42796f, 1.4325f, 1.43706f, 1.44163f, 1.44621f,
	1.45079f, 1.4554f, 1.46001f, 1.46463f, 1.46926f,
	1.47391f, 1.47856f, 1.48323f, 1.48791f, 1.4926f,
	1.4973f, 1.50201f, 1.50673f, 1.51147f, 1.51621f,
	1.52097f, 1.52574f, 1.53052f, 1.53532f, 1.54012f,
	1.54494f, 1.54976f, 1.5546f, 1.55946f, 1.56432f,
	1.5692f, 1.57408f, 1.57898f, 1.5839f, 1.58882f,
	1.59376f, 1.59871f, 1.60367f, 1.60864f, 1.61363f,
	1.61863f, 1.62364f, 1.62866f, 1.6337f, 1.63875f,
	1.64381f, 1.64889f, 1.65398f, 1.65908f, 1.66419f,
	1.66932f, 1.67446f, 1.67961f, 1.68478f, 1.68996f,
	1.69516f, 1.70036f, 1.70558f, 1.71082f, 1.71606f,
	1.72132f, 1.7266f, 1.73189f, 1.73719f, 1.74251f,
	1.74784f, 1.75318f, 1.75854f, 1.76391f, 1.7693f,
	1.7747f, 1.78012f, 1.78555f, 1.79099f, 1.79645f,
	1.80192f, 1.80741f, 1.81291f, 1.81843f, 1.82396f,
	1.82951f, 1.83507f, 1.84065f, 1.84624f, 1.85185f,
	1.85747f, 1.86311f, 1.86876f, 1.87443f, 1.88012f,
	1.88582f, 1.89153f, 1.89726f, 1.90301f, 1.90877f,
	1.91455f, 1.92035f, 1.92616f, 1.93199f, 1.93783f,
	1.94369f, 1.94957f, 1.95546f, 1.96137f, 1.96729f,
	1.97324f, 1.9792f, 1.98517f, 1.99117f, 1.99718f,
	2.0032f, 2.00925f, 2.01531f, 2.02139f, 2.02749f,
	2.0336f, 2.03973f, 2.04588f, 2.05205f, 2.05824f,
	2.06444f, 2.07066f, 2.0769f, 2.08316f, 2.08943f,
	2.09573f, 2.10204f, 2.10837f, 2.11473f, 2.12109f,
	2.12748f, 2.13389f, 2.14031f, 2.14676f, 2.15322f,
	2.15971f, 2.16621f, 2.17273f, 2.17928f, 2.18584f,
	2.19242f, 2.19902f, 2.20564f, 2.21229f, 2.21895f,
	2.22563f, 2.23233f, 2.23906f, 2.2458f, 2.25257f,
	2.25935f, 2.26616f, 2.27299f, 2.27984f, 2.28671f,
	2.2936f, 2.30051f, 2.30745f, 2.3144f, 2.32138f,
	2.32838f, 2.33541f, 2.34245f, 2.34952f, 2.35661f,
	2.36372f, 2.37086f, 2.37802f, 2.3852f, 2.3924f,
	2.39963f, 2.40688f, 2.41415f, 2.42145f, 2.42877f,
	2.43612f, 2.44349f, 2.45088f, 2.4583f, 2.46574f,
	2.47321f, 2.4807f, 2.48822f, 2.49576f, 2.50332f,
	2.51091f, 2.51853f, 2.52617f, 2.53384f, 2.54153f,
	2.54925f, 2.557f, 2.56477f, 2.57257f, 2.58039f,
	2.58824f, 2.59612f, 2.60403f, 2.61196f, 2.61992f,
	2.62791f, 2.63592f, 2.64397f, 2.65204f, 2.66014f,
	2.66826f, 2.67642f, 2.6846f, 2.69282f, 2.70106f,
	2.70933f, 2.71763f, 2.72596f, 2.73432f, 2.74271f,
	2.75113f, 2.75958f, 2.76806f, 2.77657f, 2.78512f,
	2.79369f, 2.80229f, 2.81093f, 2.8196f, 2.82829f,
	2.83702f, 2.84579f, 2.85458f, 2.86341f, 2.87227f,
	2.88117f, 2.89009f, 2.89905f, 2.90805f, 2.91708f,
	2.92614f, 2.93523f, 2.94437f, 2.95353f, 2.96273f,
	2.97197f, 2.98124f, 2.99055f, 2.99989f, 3.00927f,
	3.01869f, 3.02814f, 3.03763f, 3.04716f, 3.05672f,
	3.06632f, 3.07596f, 3.08564f, 3.09536f, 3.10511f,
	3.1149f, 3.12474f, 3.13461f, 3.14452f, 3.15447f,
	3.16447f, 3.1745f, 3.18458f, 3.19469f, 3.20485f,
	3.21505f, 3.22529f, 3.23557f, 3.2459f, 3.25627f,
	3.26668f, 3.27714f, 3.28764f, 3.29818f, 3.30877f,
	3.31941f, 3.33009f, 3.34081f, 3.35158f, 3.3624f,
	3.37326f, 3.38418f, 3.39513f, 3.40614f, 3.4172f,
	3.4283f, 3.43945f, 3.45066f, 3.46191f, 3.47321f,
	3.48456f, 3.49596f, 3.50742f, 3.51892f, 3.53048f,
	3.54209f, 3.55375f, 3.56547f, 3.57724f, 3.58906f,
	3.60094f, 3.61288f, 3.62487f, 3.63691f, 3.64901f,
	3.66117f, 3.67339f, 3.68566f, 3.698f, 3.71039f,
	3.72284f, 3.73535f, 3.74792f, 3.76056f, 3.77325f,
	3.78601f, 3.79882f, 3.81171f, 3.82465f, 3.83766f,
	3.85074f, 3.86388f, 3.87709f, 3.89036f, 3.9037f,
	3.91711f, 3.93058f, 3.94413f, 3.95774f, 3.97143f,
	3.98519f, 3.99902f, 4.01292f, 4.02689f, 4.04094f,
	4.05506f, 4.06926f, 4.08353f, 4.09788f, 4.11231f,
	4.12681f, 4.1414f, 4.15606f, 4.17081f, 4.18564f,
	4.20054f, 4.21554f, 4.23061f, 4.24577f, 4.26102f,
	4.27635f, 4.29177f, 4.30728f, 4.32288f, 4.33856f,
	4.35434f, 4.37021f, 4.38618f, 4.40224f, 4.41839f,
	4.43464f, 4.45099f, 4.46743f, 4.48398f, 4.50063f,
	4.51738f, 4.53423f, 4.55118f, 4.56824f, 4.58541f,
	4.60268f, 4.62006f, 4.63756f, 4.65516f, 4.67288f,
	4.69071f, 4.70866f, 4.72672f, 4.74491f, 4.76321f,
	4.78163f, 4.80018f, 4.81885f, 4.83765f, 4.85658f,
	4.87563f, 4.89482f, 4.91413f, 4.93359f, 4.95318f,
	4.9729f, 4.99277f, 5.01278f, 5.03293f, 5.05323f,
	5.07367f, 5.09427f, 5.11501f, 5.13591f, 5.15697f,
	5.17818f, 5.19956f, 5.2211f, 5.2428f, 5.26467f,
	5.28671f, 5.30892f, 5.33131f, 5.35387f, 5.37662f,
	5.39955f, 5.42266f, 5.44597f, 5.46946f, 5.49316f,
	5.51704f, 5.54114f, 5.56543f, 5.58993f, 5.61465f,
	5.63958f, 5.66472f, 5.69009f, 5.71569f, 5.74152f,
	5.76758f, 5.79387f, 5.82041f, 5.8472f, 5.87424f,
	5.90153f, 5.92908f, 5.9569f, 5.98499f, 6.01336f,
	6.042f, 6.07093f, 6.10015f, 6.12967f, 6.15949f,
	6.18963f, 6.22007f, 6.25084f, 6.28194f, 6.31337f,
	6.34515f, 6.37727f, 6.40976f, 6.44261f, 6.47583f,
	6.50943f, 6.54343f, 6.57782f, 6.61263f, 6.64785f,
	6.6835f, 6.71959f, 6.75613f, 6.79313f, 6.8306f,
	6.86855f, 6.907f, 6.94596f, 6.98545f, 7.02547f,
	7.06604f, 7.10717f, 7.14889f, 7.19121f, 7.23414f,
	7.27771f, 7.32193f, 7.36682f, 7.4124f, 7.4587f,
	7.50573f, 7.55352f, 7.60209f, 7.65147f, 7.7017f,
	7.75278f, 7.80476f, 7.85767f, 7.91154f, 7.9664f,
	8.0223f, 8.07925f, 8.13739f, 8.19662f, 8.25709f,
	8.31876f, 8.38177f, 8.44615f, 8.5119f, 8.57918f,
	8.64801f, 8.71847f, 8.79064f, 8.86454f, 8.94036f,
	9.01815f, 9.09804f, 9.18007f, 9.26446f, 9.35131f,
	9.44076f, 9.53296f, 9.62818f, 9.72641f, 9.82799f,
	9.93316f, 10.0421f, 10.1553f, 10.2728f, 10.3952f,
	10.5228f, 10.656f, 10.7956f, 10.9419f, 11.0956f,
	11.2577f, 11.4292f, 11.611f, 11.8045f, 12.0114f,
	12.2338f, 12.4737f, 12.7349f, 13.0207f, 13.3368f,
	13.6901f, 14.0904f, 14.5531f, 15.1f, 15.7685f,
	16.6315f, 17.8505f, 19.9282f, 39.3416f
};

void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of the Whitted-syle light transport algorithm (E [S*] (D|G) L)
//
// This function is the function that compute the color at the intersection point
// of a ray defined by a position and a direction. Note that thus function is recursive (it calls itself).
//
// If the material of the intersected object is either reflective or reflective and refractive,
// then we compute the reflection/refracton direction and cast two new rays into the scene
// by calling the castRay() function recursively. When the surface is transparent, we mix
// the reflection and refraction color using the result of the fresnel equations (it computes
// the amount of reflection and refractin depending on the surface normal, incident view direction
// and surface refractive index).
//
// If the surface is duffuse/glossy we use the Phong illumation model to compute the color
// at the intersection point.
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    if (depth > this->maxDepth) {
        return Vector3f(0.0,0.0,0.0);
    }
    Intersection intersection = Scene::intersect(ray);
    Material *m = intersection.m;
    Object *hitObject = intersection.obj;
    Vector3f hitColor = this->backgroundColor;
//    float tnear = kInfinity;
    Vector2f uv;
    uint32_t index = 0;
    if(intersection.happened) {
        //return Vector3f(0, 0, 0);
        //std::cout << "hit " << intersection.coords << std::endl;
        Vector3f hitPoint = intersection.coords;
        Vector3f N = intersection.normal; // normal
        Vector2f st; // st coordinates
        hitObject->getSurfaceProperties(hitPoint, ray.direction, index, uv, N, st);
//        Vector3f tmp = hitPoint;
        switch (m->getType()) {
            case REFLECTION_AND_REFRACTION:
            {
                hitPoint = computeReflectionAndFefraction(ray, depth, hitPoint, N, m);
                break;
            }
            case REFLECTION:
            {
                hitColor = computeReflection(ray, depth, hitPoint, N, m);
				break;
            }
           case DIFFUSE_AND_GLOSSY :
            {
			   hitColor = computeDiffuseAndGlossy(ray, depth, hitPoint, N, m, st, hitObject);
                break;
            }
           case SUBSURFACE_SCATTERING: 
           {
			   //hitColor = computeDiffuseAndGlossy(ray, depth, hitPoint, N, m, st, hitObject);
               hitColor = computeSubsurfaceScattering(ray, depth, hitPoint, N, m, st, hitObject);
           }
        }
    }

    return hitColor;
}

    // Compute Fresnel equation
//
// \param I is the incident view direction
//
// \param N is the normal at the intersection point
//
// \param ior is the material refractive index
//
// \param[out] kr is the amount of light reflected
    static void fresnel(const Vector3f &I, const Vector3f &N, const float &ior, float &kr)
    {
        float cosi = clamp(-1, 1, dotProduct(I, N));
        float etai = 1, etat = ior;
        if (cosi > 0) {  std::swap(etai, etat); }
        // Compute sini using Snell's law
        float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
        // Total internal reflection
        if (sint >= 1) {
            kr = 1;
        }
        else {
            float cost = sqrtf(std::max(0.f, 1 - sint * sint));
            cosi = fabsf(cosi);
            float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
            float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
            kr = (Rs * Rs + Rp * Rp) / 2;
        }
        // As a consequence of the conservation of energy, transmittance is given by:
        // kt = 1 - kr;
    }
Vector3f Scene::computeReflectionAndFefraction(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m) const
{
	Vector3f reflectionDirection = normalize(reflect(ray.direction, N));
	Vector3f refractionDirection = normalize(refract(ray.direction, N, m->ior));
	Vector3f reflectionRayOrig = (dotProduct(reflectionDirection, N) < 0) ?
								 hitPoint - N * EPSILON :
								 hitPoint + N * EPSILON;
	Vector3f refractionRayOrig = (dotProduct(refractionDirection, N) < 0) ?
								 hitPoint - N * EPSILON :
								 hitPoint + N * EPSILON;
	Vector3f reflectionColor = castRay(Ray(reflectionRayOrig, reflectionDirection), depth + 1);
	Vector3f refractionColor = castRay(Ray(refractionRayOrig, refractionDirection), depth + 1);
	float kr;
	fresnel(ray.direction, N, m->ior, kr);
	return reflectionColor * kr + refractionColor * (1 - kr);
}
Vector3f Scene::computeReflection(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m) const
{
    float kr;
	fresnel(ray.direction, N, m->ior, kr);
	Vector3f reflectionDirection = reflect(ray.direction, N);
	Vector3f reflectionRayOrig = (dotProduct(reflectionDirection, N) < 0) ?
								 hitPoint + N * EPSILON :
								 hitPoint - N * EPSILON;
	return  castRay(Ray(reflectionRayOrig, reflectionDirection),depth + 1) * kr;
}
Vector3f Scene::computeDiffuseAndGlossy(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m, const Vector2f& st, Object * hitObject) const
{
	// [comment]
	// We use the Phong illumation model int the default case. The phong model
	// is composed of a diffuse and a specular reflection component.
	// [/comment]
	Vector3f lightAmt = 0, specularColor = 0;
	Vector3f shadowPointOrig = (dotProduct(ray.direction, N) < 0) ?
							   hitPoint + N * EPSILON :
							   hitPoint - N * EPSILON;
	// [comment]
	// Loop over all lights in the scene and sum their contribution up
	// We also apply the lambert cosine law
	// [/comment]
	for (uint32_t i = 0; i < get_lights().size(); ++i)
	{
		auto area_ptr = dynamic_cast<AreaLight*>(this->get_lights()[i].get());
		if (area_ptr)
		{
			// Do nothing for this assignment
		}
		else
		{
			Vector3f lightDir = get_lights()[i]->position - hitPoint;
			// square of the distance between hitPoint and the light
			float lightDistance2 = dotProduct(lightDir, lightDir);
			lightDir = normalize(lightDir);
			float LdotN = std::max(0.f, dotProduct(lightDir, N));
			Object *shadowHitObject = nullptr;
			float tNearShadow = kInfinity;
			// is the point in shadow, and is the nearest occluding object closer to the object than the light itself?
			bool inShadow = bvh->Intersect(Ray(shadowPointOrig, lightDir)).happened;
			lightAmt += (1 - inShadow) * get_lights()[i]->intensity * LdotN;
			Vector3f reflectionDirection = reflect(-lightDir, N);
			specularColor += powf(std::max(0.f, -dotProduct(reflectionDirection, ray.direction)),
								  m->specularExponent) * get_lights()[i]->intensity;
		}
	}
	return lightAmt * (hitObject->evalDiffuseColor(st) * m->Kd + specularColor * m->Ks);
}
static Vector3f toWorld(const Vector3f& a, const Vector3f& N) {
	Vector3f B, C;
	if (std::fabs(N.x) > std::fabs(N.y)) {
		float invLen = 1.0f / std::sqrt(N.x * N.x + N.z * N.z);
		C = Vector3f(N.z * invLen, 0.0f, -N.x * invLen);
	}
	else {
		float invLen = 1.0f / std::sqrt(N.y * N.y + N.z * N.z);
		C = Vector3f(0.0f, N.z * invLen, -N.y * invLen);
	}
	B = crossProduct(C, N);
	return a.x * B + a.y * C + a.z * N;
}
static float Rd(float r, float d)
{
	if (r == 0.0f)
		return 0.0f;
	return (std::exp(-r / d) + std::exp(-r / (3.0f * d))) /(8.0f * M_PI * d * r);
}
static Vector3f Rd(float r, const Vector3f& D)
{
	return Vector3f(Rd(r, D.x), Rd(r, D.y), Rd(r, D.z));
}
static float sampleR(float r, float d)
{
	float offset = std::min(r * LUTSize, LUTSize - 1.0f);
	const int ib = (int)offset;
	const int iu = (int)(offset + 1.0f);
	const float distance = LUT[ib] * (1 - offset + ib) + LUT[iu] * (offset - ib);
	return distance * d;
}
static float pdfR(float r, float d)
{
	return Rd(r, d) * M_PI * 2.0f * r;
}
bool Scene::samplePoint(const Vector3f & source, const Vector3f & D, const Vector3f& N, Vector3f & target, float & pdf) const
{
	//get one d with random channel
	int channel = (int)std::min(3.0f * get_random_float(), 2.0f);
	auto d = D[channel];
	auto r = sampleR(get_random_float(), d);
	auto R = sampleR(0.996f, d);
	if (r > R)
		return false;
	float theta = 2.0 * M_PI * get_random_float();
	Vector3f local_dir(std::cos(theta), std::sin(theta), 0.0);
	auto dir = toWorld(normalize(local_dir), N);
	Vector3f pos = source + dir * r;
	//Vector3f T = normalize(pos - source);
	//auto d = dotProduct(T, N);
	//std::cout << d << std::endl;
	Ray ray = Ray(pos, -N);
    Intersection inter = Scene::intersect(ray);
	target = inter.coords;
	auto dot = dotProduct(N, inter.normal);
	if (dot < 0)
		dot = EPSILON;
	pdf = pdfR(r, d);
}
static Vector3f S(const Vector3f& po, const Vector3f& wo, const Vector3f& No, float ioro,
	const Vector3f& pi, const Vector3f& wi, const Vector3f& Ni, float iori, const Vector3f& D)
{
    float kro;
	fresnel(wo, No, ioro, kro);
	float kri;
	fresnel(wi, Ni, iori, kri);
	//float d = std::abs(po.x - pi.x) + std::abs(po.y - pi.y) + std::abs(po.z - pi.z);
	float d = sqrt(dotProduct(po - pi, po - pi));
	return Rd(d, D) * (1 - kro) * (1 - kri) / M_PI;
}
static Vector3f S(const Vector3f& po, const Vector3f& pi, const Vector3f& D)
{
	float d = sqrt(dotProduct(po - pi, po - pi));
	return Rd(d, D) / M_PI;
}
Vector3f Scene::computeSubsurfaceScattering(const Ray &ray, int depth, const Vector3f& po, const Vector3f& No, Material * mo, const Vector2f& st, Object * hitObject) const
{
	Vector3f sumLightColor = Vector3f(0);
	for (uint32_t i = 0; i < get_lights().size(); ++i)
	{
		auto area_ptr = dynamic_cast<AreaLight*>(this->get_lights()[i].get());
		if (area_ptr)
		{
			// Do nothing for this assignment
		}
		else
		{
			Vector3f lightDir = get_lights()[i]->position - po;
			// square of the distance between hitPoint and the light
			float lightDistance2 = dotProduct(lightDir, lightDir);
			lightDir = normalize(lightDir);
			float LdotN = std::max(0.f, dotProduct(lightDir, No));
			Vector3f reflectionDirection = reflect(-lightDir, No);
			sumLightColor += powf(std::max(0.f, -dotProduct(reflectionDirection, ray.direction)),
				mo->specularExponent) * get_lights()[i]->intensity * mo->Ks;
		}
	}
	Vector2f ist; // st coordinates
	uint32_t index = 0;
	Vector2f iuv;
	Vector3f sample;
	float pdf; 
	if(!samplePoint(po, mo->D, No, sample , pdf))
		return sumLightColor;
	for (uint32_t i = 0; i < get_lights().size(); ++i)
	{
		auto area_ptr = dynamic_cast<AreaLight*>(this->get_lights()[i].get());
		if (area_ptr)
			continue;
		
		Vector3f inLightDir = sample - get_lights()[i]->position ;
		inLightDir = normalize(inLightDir);
		auto inter = Scene::intersect(Ray(get_lights()[i]->position, inLightDir));
		if (!inter.happened)
			continue;
		Material* mi = inter.m;
		Object* inObject = inter.obj;
		const Vector3f& pi = inter.coords;
		Vector3f Ni = inter.normal; // normal


		inObject->getSurfaceProperties(pi, inLightDir, index, iuv, Ni, ist);
		float LdotN = std::max(0.f, dotProduct(-inLightDir, Ni));
		auto light =  get_lights()[i]->intensity * LdotN;
		auto s = S(po, -ray.direction, No, 1.0 / mo->ior, pi, inLightDir, Ni, mi->ior, mi->D) / pdf;
		auto diffColor = mi->Kd * light * inObject->evalDiffuseColor(ist) * s;
		sumLightColor += diffColor;
	}
	
	return sumLightColor;
}