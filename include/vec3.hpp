#pragma once


class vec3{
    private:
        double e[3];
    public:
        vec3() : e{0,0,0}{}
        vec3(double e0, double e1 , double e2): e{e0, e1, e2}{}

        double x() const { return e[0];}
        double y() const { return e[1];}
        double z() const { return e[2];}

        vec3 operator-() const { return vec3(-e[0],-e[1],-e[2]);}
        double operator[](int i ) const{ return e[i];}
        double& operator[](int i ) {return e[i];}

        vec3& operator+=(const vec3& v){
            e[0]+=v.x();
            e[1]+=v.y();
            e[2]+=v.z();

            return *this;
        }


        vec3& operator*=(double t){
            e[0]*=t;
            e[1]*=t;
            e[2]*=t;

            return *this; 
        }


        vec3& operator/=(double t){
            return *this *= 1/t;
        }

        double lengthsqaured() const{
            return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
        }

        double length() const{
            return std::sqrt(lengthsqaured());
        }

        static vec3 random(){
            return vec3(randomDouble(),randomDouble(),randomDouble());
        }

        static vec3 random(double min, double max){
            return vec3(randomDouble(min, max),randomDouble(min, max),randomDouble(min, max));
        }

        bool nearZero() const{
            auto s = 1e-8;
            return ((std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s));
        }
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out<< v.x() << ' '<< v.y() << ' '<< v.z();
}

inline vec3 operator+(const vec3&  u, const vec3& v)
{
    return vec3{u.x()+v.x(),u.y()+v.y(),u.z()+v.z()};
}

inline vec3 operator-(const vec3&  u, const vec3& v)
{
    return vec3{u.x()-v.x(),u.y()-v.y(),u.z()-v.z()};
}

inline vec3 operator*(const vec3&  u, const vec3& v)
{
    return vec3{u.x()*v.x(),u.y()*v.y(),u.z()*v.z()};
}

inline vec3 operator*(double t, const vec3& v)
{
    return vec3{t*v.x(),t*v.y(),t*v.z()};
}

inline vec3 operator*(const vec3& v, double t)
{
    return t * v;
}

inline vec3 operator/(const vec3&v, double t){
    return (1/t) * v;
}

inline double dot(const vec3&  u, const vec3& v)
{
    return (u.x()*v.x()+u.y()*v.y()+u.z()*v.z());
}

inline vec3 cross(const vec3&  u, const vec3& v)
{
    return vec3(u.y()*v.z() - u.z()*v.y(), u.z()*v.x()-u.x()*v.z(), u.x()*v.y()-u.y()*v.x());
}

inline vec3 unit_vector(const vec3& v){
    return v / v.length();
}

inline vec3  randomUnitVector(){
    while(true){
        // a random point in the square
        auto p = vec3::random(-1,1);
        auto len = p.lengthsqaured();
        if(len <= 1){
            return (p / std::sqrt(len));
        }
    }
}

inline vec3 randomOnHemisphere(const vec3& normal){
    vec3 randomUnitSphere = randomUnitVector();
    //if the dot product is in the same direction, return it
    if(dot(randomUnitSphere, normal) > 0.0){
        return randomUnitSphere;
    }else{
        //else change the direction
        return -randomUnitSphere;
    }
}
// so this caluclated how the ray is reflected.
// let say v is the incoming ray and n is the surface noraml.
//v can be divided into two rays, one parallet to the surface, one  parallet to the normal.
// to find the second one we can do v.n cos(theta), now to scale it along the normal multiply with n
// let this be b = dot(v,n) * n
// to calculate the first part (parralel to the surface) = v-b;

// now to get the reflected ray from the metal surface, this is shoudld be the addition of both the parts (b should be direction of the normal)
// reflected ray = (v-b)+(-b) = v-2b = v- 2* dot(v,n)*n;
inline vec3 reflect(const vec3& v, const vec3& n){
    return v - 2*dot(v,n)*n;
}


//read more about refraction here
//https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
inline vec3 refract(const vec3& uv, const vec3& n, double refractiveIndex){
auto cosTheta = std::fmin(dot(-uv,n), 1.0);
vec3 rperpendicular = refractiveIndex * (uv + cosTheta*n);
vec3 rparrallel = -std::sqrt(std::fabs(1.0-rperpendicular.lengthsqaured())) * n;

return rperpendicular + rparrallel;
}

