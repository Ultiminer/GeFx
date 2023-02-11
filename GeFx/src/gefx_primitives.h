#ifndef GEFX_PRIMITIVES_H_
#define GEFX_PRIMITIVES_H_
#include <gcem.hpp>
#include <vector>
#include <algorithm>

namespace Ge{
    constexpr float PI2{6.2832};
// PRIMITIVE DEFINITIONS 
    struct Vec2D
    {
        union{struct{float x; float y;}; struct{float el[2];};};
    };
    struct Vec3D{
        union{struct{float x; float y; float z;};struct{float el[3];};struct{Vec2D p2;};};
    };
     struct Vec4D{
        union{struct{float x; float y; float z;float w;};struct{float el[4];};struct{Vec3D p3;};};
    };
     struct Vec5D{
        union{struct{float x; float y; float z;float w; float v;};struct{float el[5];};struct{Vec2D p4;};};
    };
     struct Vec6D{
        union{struct{float x; float y; float z;float w; float v; float u;};struct{float el[6];};struct{Vec2D p5;};};
    };
    struct Line2D{
        union{struct{float x1; float y1; float x2; float y2;}; struct{Vec2D a; Vec2D b;}; struct{float el[4];};};
    };
    struct Line3D{
        union{struct{float x1; float y1; float z1; float x2; float y2; float z2;}; struct{Vec3D a; Vec3D b;}; struct{float el[6];};};
    };
    struct Box2D{
        union{struct{float x; float y; float width; float height;}; struct{Vec2D pos; Vec2D dim;}; struct{float el[4];};}; 
    };
    struct Rect{
        union{struct{float x; float y; float width; float height; float angle;}; struct{Vec2D pos; Vec2D dim;}; struct{Box2D box;};struct{float el[5];};};
    };
    struct Box3D{
        union{struct{float x; float y; float z; float width; float height; float length; }; struct{Vec3D pos; Vec3D dim;}; struct{float el[6];};}; 
    };
    struct Cube{
        union{struct{float x; float y; float z; float width; float height; float length; float alpha; float beta; float gamma;}; struct{Vec3D pos; Vec3D dim;Vec3D angle;}; struct{Box3D box;}; struct{float el[9];};};
    };
    struct Mat2x2{
        union{struct{float r1c1; float r1c2; float r2c1; float r2c2;}; struct{Vec2D a; Vec2D b;}; struct{float el[4];};};
    };
    struct Mat3x3{
        union{struct{float r1c1; float r1c2; float r1c3; float r2c1; float r2c2; float r2c3; float r3c1; float r3c2; float r3c3;}; struct{Vec3D a; Vec3D b; Vec3D c;}; struct{float el[9];};};
    };
    struct Mat2x3{
        union{struct{float r1c1; float r1c2; float r1c3; float r2c1; float r2c2; float r2c3;};struct{Vec3D a; Vec3D b;};};
    };
    struct Circle{
        union{struct{float x; float y; float r;};struct{Vec2D pos;};struct{float el[3];};};
    };
    struct Sphere{
        union{struct{float x; float y; float z; float r;};struct{Vec3D pos;};struct{float el[4];};};
    };

    struct Polygon{
        union{struct{float x; float y; float r; size_t n; float angle;};struct{Vec2D pos;};};
    };
//Interprets
    constexpr Vec2D interpret_vec(const float x, const float y)
    {
        return {x,y};
    }
    constexpr Vec3D interpret_vec(const float x, const float y, const float z)
    {
        return {x,y,z};
    }
    constexpr Vec4D interpret_vec(const float x, const float y, const float z, const float w)
    {
        return {x,y,z,w};
    }
    constexpr Vec5D interpret_vec(const float x, const float y, const float z, const float w, const float v)
    {
        return {x,y,z,w,v};
    }
    constexpr Vec6D interpret_vec(const float x, const float y, const float z, const float w, const float v, const float u)
    {
        return {x,y,z,w,v,u};
    }
//OPERATOR OVERLOADS FOR VEC2D VEC3D
 //2D
    constexpr Vec2D operator+(const Vec2D& a, const Vec2D& b)
    {
        return {a.x+b.x, a.y+b.y};
    }
    constexpr Vec2D operator-(const Vec2D& a, const Vec2D& b)
    {
        return {a.x-b.x, a.y-b.y};
    }
    constexpr float operator*(const Vec2D& a, const Vec2D& b)
    {
        return a.x*b.x+a.y*b.y;
    }
    constexpr Vec2D operator*(const Vec2D& a, const float& x)
    {
        return {a.x*x,a.y*x};
    }
    constexpr Vec2D operator/(const Vec2D& a, const float& x)
    {
        return {a.x/x,a.y/x};
    }
//3D 
    constexpr Vec3D operator+(const Vec3D& a, const Vec3D& b)
    {
        return {a.x+b.x, a.y+b.y,a.z+b.z};
    }
    constexpr Vec3D operator-(const Vec3D& a, const Vec3D& b)
    {
        return {a.x-b.x, a.y-b.y,a.z-b.z};
    }
    constexpr float operator*(const Vec3D& a, const Vec3D& b)
    {
        return a.x*b.x+a.y*b.y+a.z*b.z;
    }
    constexpr Vec3D operator*(const Vec3D& a, const float& x)
    {
        return {a.x*x,a.y*x,a.z*x};
    }
    constexpr Vec3D operator/(const Vec3D& a, const float& x)
    {
        return {a.x/x,a.y/x,a.z/x};
    }
    constexpr float Cross(const Vec2D& a, const Vec2D& b)
    {
        return a.x*b.y-a.y*b.x;
    }
    constexpr Vec3D Cross(const Vec3D& a, const Vec3D& b)
    {
        return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.x,a.x*b.y-a.y*b.x};
    }
// Matrix multiplication and addition
    //2D Matricies
    constexpr Mat2x2 operator+(const Mat2x2& a, const Mat2x2& b)
    {
        return {a.r1c1+b.r1c1,a.r1c2+b.r1c2,a.r2c1+b.r2c1,a.r2c2+b.r2c2};
    }
    constexpr Mat2x2 operator-(const Mat2x2& a, const Mat2x2& b)
    {
        return {a.r1c1-b.r1c1,a.r1c2-b.r1c2,a.r2c1-b.r2c1,a.r2c2-b.r2c2};
    }
    constexpr Mat2x2 operator*(const Mat2x2& a, const Mat2x2& b)
    {
        return {a.a*b.a,a.a*b.b,a.b*b.a,a.b*b.b};
    }
    constexpr Mat2x2 operator*(const Mat2x2& mat, const float& x)
    {
        return {mat.r1c1*x,mat.r1c2*x,mat.r2c1*x,mat.r2c2*x};
    }
    constexpr Mat2x2 operator/(const Mat2x2& mat, const float& x)
    {
        return {mat.r1c1/x,mat.r1c2/x,mat.r2c1/x,mat.r2c2/x};
    }
    constexpr Vec2D operator*(const Mat2x2& mat, const Vec2D& vec)
    {
        return {mat.r1c1*vec.x+mat.r1c2*vec.y, mat.r2c1*vec.x+mat.r2c2*vec.y};
    }
//Mat3x2
    constexpr Mat2x3 operator+(const Mat2x3& a, const Mat2x3& b)
    {
        return {a.r1c1+b.r1c1,a.r1c2+b.r1c2,a.r1c3+b.r1c3,a.r2c1+b.r2c1,a.r2c2+b.r2c2,a.r2c3+b.r2c3};
    }
    constexpr Mat2x3 operator-(const Mat2x3& a, const Mat2x3& b)
    {
        return {a.r1c1-b.r1c1,a.r1c2-b.r1c2,a.r1c3-b.r1c3,a.r2c1-b.r2c1,a.r2c2-b.r2c2,a.r2c3-b.r2c3};
    }
    constexpr Mat2x3 operator*(const Mat2x3& mat, const float& x)
    {
        return {mat.r1c1*x,mat.r1c2*x,mat.r1c3*x,mat.r2c1*x,mat.r2c2*x,mat.r2c3*x};
    }
    constexpr Mat2x3 operator/(const Mat2x3& mat, const float& x)
    {
        return {mat.r1c1/x,mat.r1c2/x,mat.r1c3/x,mat.r2c1/x,mat.r2c2/x,mat.r2c3/x};
    }
    constexpr Vec2D operator*(const Mat2x3& mat, const Vec3D& vec)
    {
        return {mat.r1c1*vec.x+mat.r1c2*vec.y+mat.r1c3*vec.z, mat.r2c1*vec.x+mat.r2c2*vec.y+mat.r2c3*vec.z};
    }
//3D Matricies
    constexpr Mat3x3 operator+(const Mat3x3& a, const Mat3x3& b)
    {
        return {a.r1c1+b.r1c1,a.r1c2+b.r1c2,a.r1c3+b.r1c3,a.r2c1+b.r2c1,a.r2c2+b.r2c2,a.r2c3+b.r2c3,a.r3c1+b.r3c1,a.r3c2+b.r3c2,a.r3c3+b.r3c3};
    }
    constexpr Mat3x3 operator-(const Mat3x3& a, const Mat3x3& b)
    {
        return {a.r1c1-b.r1c1,a.r1c2-b.r1c2,a.r1c3-b.r1c3,a.r2c1-b.r2c1,a.r2c2-b.r2c2,a.r2c3-b.r2c3,a.r3c1-b.r3c1,a.r3c2-b.r3c2,a.r3c3-b.r3c3};
    }
    constexpr Mat3x3 operator*(const Mat3x3& a, const Mat3x3& b)
    {
        return {a.a*b.a,a.a*b.b,a.a*b.c,a.b*b.a,a.b*b.b, a.b*b.c,a.c*b.a,a.c*b.b,a.c*b.c};
    }
    constexpr Mat3x3 operator*(const Mat3x3& mat, const float& x)
    {
        return {mat.r1c1*x,mat.r1c2*x,mat.r1c3*x,mat.r2c1*x,mat.r2c2*x,mat.r2c3*x,mat.r3c1*x,mat.r3c2*x,mat.r3c3*x};
    }
    constexpr Mat3x3 operator/(const Mat3x3& mat, const float& x)
    {
        return {mat.r1c1/x,mat.r1c2/x,mat.r1c3/x,mat.r2c1/x,mat.r2c2/x,mat.r2c3/x,mat.r3c1/x,mat.r3c2/x,mat.r3c3/x};
    }
    constexpr Vec3D operator*(const Mat3x3& mat, const Vec3D& vec)
    {
        return {mat.r1c1*vec.x+mat.r1c2*vec.y+ mat.r1c3*vec.z, mat.r2c1*vec.x+mat.r2c2*vec.y+mat.r2c3*vec.z, mat.r3c1*vec.x+mat.r3c2*vec.y+mat.r3c3*vec.z};
    }

    constexpr float Det2(const Mat2x2& mat)
    {
        return mat.r1c1*mat.r2c2-mat.r1c2*mat.r2c1;
    }
    constexpr float Det3(const Mat3x3& mat)
    {
        return mat.r1c1*Det2({mat.r2c2,mat.r2c3,mat.r3c2,mat.r3c3})-mat.r1c2*Det2({mat.r1c2,mat.r1c3,mat.r3c2,mat.r3c3})+mat.r1c3*Det2({mat.r1c2,mat.r1c3,mat.r2c2,mat.r2c3});
    }
    // PREDFINIED CONSTANTS 
    constexpr float PI{3.1415926f};
    constexpr float EPSILON{0.001f};
    constexpr Mat2x2 CRONECKER2D{1,0,0,1};
    constexpr Mat3x3 CRONECKER3D{1,0,0 ,0,1,0 ,0,0,1};
    constexpr Mat2x2 UNO2D{1,1,1,1};
    constexpr Mat3x3 UNO3D{1,1,1 ,1,1,1, 1,1,1};
    constexpr Vec2D PolarVec(const float& angle)
    {
        return {gcem::cos(angle),gcem::sin(angle)};
    }
    constexpr Vec3D SphericalVec(const float& theta, const float& phi)
    {
        const float st{gcem::sin(theta)};
        const float ct{gcem::cos(theta)};
        const float sp{gcem::sin(phi)};
        const float cp{gcem::cos(phi)};

        return {st*cp,st*sp,ct};
    }
    constexpr Mat2x2 RotMat2D(const float& angle)
    {
        const float c{gcem::cos(angle)};
        const float s{gcem::sin(angle)};
        return {c,-s,s,c};
    }
    
    constexpr Mat3x3 RotMat3Dx(const float& angle)
    {
        const float c{gcem::cos(angle)};
        const float s{gcem::sin(angle)};
        return {1,0,0, 0,c,-s, 0,s,c};
    }
    constexpr Mat3x3 RotMat3Dy(const float& angle)
    {
        const float c{gcem::cos(angle)};
        const float s{gcem::sin(angle)};
        return {c,0,s,0,1,0,-s,0,c};
    }
    constexpr Mat3x3 RotMat3Dz(const float& angle)
    {
        const float c{gcem::cos(angle)};
        const float s{gcem::sin(angle)};
        return {c,-s,0 ,s,c,0 ,0,0,1};
    }
    constexpr Mat3x3 RotMat3Dx(const float& c, const float& s)
    {
        return {1,0,0, 0,c,-s, 0,s,c};
    }
    constexpr Mat3x3 RotMat3Dy(const float& c, const float& s)
    {
        return {c,0,s,0,1,0,-s,0,c};
    }
    constexpr Mat3x3 RotMat3Dz(const float& c, const float& s)
    {
        return {c,-s,0 ,s,c,0 ,0,0,1};
    }
    //Here {alpha, beta, gamma} are assumed to be the euler angles
    constexpr Mat3x3 RotMat3D(const float& alpha, const float& beta, const float& gamma)
    {
        return RotMat3Dz(alpha)*RotMat3Dy(beta)*RotMat3Dz(gamma);
    }
    constexpr Mat3x3 RotMat3D(const float angle, const Vec3D u)
    {
        const Vec3D axis=u*gcem::inv_sqrt(u*u);
        const float c{gcem::cos(angle)};
        const float s{gcem::sin(angle)};
        const float C{1-c};
        return {axis.x*axis.x*C+c,axis.x*axis.y*C-axis.z*s,axis.x*axis.z*C+axis.y*s, axis.y*axis.x*C+axis.z*s, axis.y*axis.y*C+c, axis.y*axis.z*C-axis.x*s,axis.z*axis.x*C-axis.y*s,axis.z*axis.y*C+axis.x*s,axis.z*axis.z*C+c};
    }    

    constexpr float square(const float& x)
    {
        return x*x;
    }
    constexpr Vec2D floor(const Vec2D& vec)
    {
        return {gcem::floor(vec.x),gcem::floor(vec.y)};
    }
    constexpr Vec2D xdir{1,0};
    constexpr Vec2D ydir{0,1};
    constexpr Vec3D xdir3{1,0,0};
    constexpr Vec3D ydir3{0,1,0};
    constexpr Vec3D zdir{0,0,1};
}



#endif