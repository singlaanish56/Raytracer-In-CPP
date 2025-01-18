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
        if(len > 1e-160 && len<=1){
            return p/sqrt(len);
        }
    }
}

inline vec3 randomOnHemisphere(const vec3& normal){
    vec3 randomUnitSphere = randomUnitVector();
    //if the dot product is in the same direction, return it
    if(dot(randomUnitSphere, normal) > 0.0){
        return randomUnitSphere;
    }

    //else change the direction
    return -randomUnitSphere;
}
