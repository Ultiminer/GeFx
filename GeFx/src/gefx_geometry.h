#ifndef GEFX_GEOMETRY_H_
#define GEFX_GEOMETRY_H_
#include "gefx_primitives.h"
#include <algorithm>
#include <functional>
#include <vector>

namespace Ge{
constexpr float ComponentDivison(const Vec2D& a, const Vec2D& b)
{
    return (a.x/b.x+a.y/b.y)*0.5f; 
}
constexpr float ComponentDivison(const Vec3D& a, const Vec3D& b)
{
    return (a.x/b.x+a.y/b.y+a.z/b.z)*0.3333333333f; 
}
constexpr float ComponentDivison(const Vec4D& a, const Vec4D& b)
{
    return (a.x/b.x+a.y/b.y+a.z/b.z+a.w/b.w)*0.25f; 
}
constexpr float ComponentDivison(const Vec5D& a, const Vec5D& b)
{
    return (a.x/b.x+a.y/b.y+a.z/b.z+a.w/b.w+a.v/b.v)*0.2f; 
}
constexpr float Dist(const Vec2D& vec)
{
    return gcem::sqrt(vec*vec);
}
constexpr Vec2D Normalize(const Vec2D& vec)
{
    return vec*gcem::inv_sqrt(vec*vec);
}
constexpr float Dist(const Vec3D& vec)
{
    return gcem::sqrt(vec*vec);
}
constexpr Vec3D Normalize(const Vec3D& vec)
{
    return vec*gcem::inv_sqrt(vec*vec);
}
constexpr float Dist(const Line2D& line)
{
    return Dist(line.b-line.a);
}
constexpr float Dist(const Line3D& line)
{
    return Dist(line.b-line.a);
}
constexpr float Squaredist(const Vec2D& a, const Vec2D& b)
{
    const Vec2D d= b-a; 
    return d*d;
}
constexpr float Squaredist(const Vec3D& a, const Vec3D& b)
{
    const Vec3D d= b-a; 
    return d*d;
}
constexpr float Squaredist(const Vec2D& vec)
{
    return vec*vec;
}
constexpr float Squaredist(const Vec3D& vec)
{
    return vec*vec;
}
constexpr float Squaredist(const Line2D& line)
{
    return Squaredist(line.a,line.b);
}
constexpr float Squaredist(const Line3D& line)
{
    return Squaredist(line.a,line.b);
}

constexpr Vec2D ProjectPara(const Vec2D& a, const Vec2D& b)
{
    return b*(a*b)/(b*b); 
}
constexpr Vec2D ProjectOrtho(const Vec2D& a, const Vec2D& b)
{
    return a-b*(a*b)/(b*b); 
}
constexpr Vec3D ProjectPara(const Vec3D& a, const Vec3D& b)
{
    return b*(a*b)/(b*b); 
}
constexpr Vec3D ProjectOrtho(const Vec3D& a, const Vec3D& b)
{
    return a-b*(a*b)/(b*b); 
}
constexpr float SinSquared(const Vec2D& a, const Vec2D& b)
{
    return square(Cross(a,b))/((a*a)*(b*b));
}
constexpr float CosSquared(const Vec2D& a, const Vec2D& b)
{
    return square(a*b)/((a*a)*(b*b));
}
constexpr float SinSquared(const Vec3D& a, const Vec3D& b)
{
    return Squaredist(Cross(a,b))/((a*a)*(b*b));
}
constexpr float CosSquared(const Vec3D& a, const Vec3D& b)
{
    return square(a*b)/((a*a)*(b*b));
}
constexpr Vec2D Normal(const Vec2D& vec)
{
    return {-vec.y,vec.x};
}
constexpr Vec2D UnitNormal(const Vec2D& vec)
{
    return Normalize(Normal(vec));
}
constexpr Vec2D UnitNormal(const Vec2D& A, const Vec2D& B)
{
    const Vec2D d=B-A;
    return Normalize(Normal(d));
}
constexpr Vec2D CombinedUnitNormal(const Vec2D& u, const Vec2D& v)
{
    return Normalize(UnitNormal(u)+UnitNormal(v));
}

constexpr Vec2D Rotate(const Vec2D& vec, const Vec2D& center, const float angle)
{
    return center+RotMat2D(angle)*(vec-center);
}
constexpr Line2D Rotate(const Line2D& line, const Vec2D center, const float angle)
{
    const Vec2D ta = Rotate(line.a, center, angle);
    const Vec2D tb = Rotate(line.b, center, angle);
    return {ta.x,ta.y,tb.x,tb.y};
}
constexpr Vec3D Rotate(const Vec3D& vec, const Vec3D& center, const float angle, const Vec3D& axis)
{
    return center+RotMat3D(angle,axis)*(vec-center);
}
constexpr Vec3D Rotate(const Vec3D& vec, const Vec3D& center, const float alpha, const float beta, const float gamma)
{
    return center+RotMat3D(alpha,beta,gamma)*(vec-center);
}
constexpr Line3D Rotate(const Line3D& line, const Vec3D& center, const float angle, const Vec3D& axis)
{
    const Vec3D ta=Rotate(line.a,center, angle,axis);
    const Vec3D tb=Rotate(line.b,center, angle,axis);

    return {ta.x,ta.y,ta.z,tb.x,tb.y,tb.z};
}

constexpr bool Between(const float& x, const float& a, const float& b)
{
    return (x>a)?(x<=b):(x>=b);
}
constexpr bool PointIn(const Vec2D& a, const Vec2D& b)
{
    return a.x==b.x&&a.y==b.y;
}
constexpr bool PointIn(const Vec3D& a, const Vec3D& b)
{
    return a.x==b.x&&a.y==b.y&&a.z==b.z;
}
constexpr bool PointIn(const Vec2D& p, const Circle& circle)
{
    return Squaredist(p,circle.pos)<=square(circle.r);
}
constexpr bool PointIn(const Vec3D& p, const Sphere& sphere)
{
    return Squaredist(p,sphere.pos)<=square(sphere.r);
}
constexpr bool PointIn(const Vec2D& p, const Box2D& box)
{
    return (box.x+box.width>=p.x)&&(box.y+box.height>=p.y)&&(p.x>=box.x)&&(p.y>=box.y);
}
constexpr bool PointIn(const Vec3D& p, const Box3D& box)
{
    return (box.x+box.width>=p.x)&&(box.y+box.height>=p.y)&&(box.z+box.length>=p.z)&&(p.x>=box.x)&&(p.y>=box.y)&&(p.z>=box.z);
}
constexpr bool PointIn(const Vec2D& p, const Line2D& line)
{
    if(!Between(p.x,line.a.x,line.b.x)||!Between(p.y,line.a.y,line.b.y))return false;
    const Vec2D da = line.a-p;
    const Vec2D db = line.b-p;
    return CosSquared(da,db)>1-EPSILON;
}
constexpr bool PointIn(const Vec3D& p, const Line3D& line)
{
    if(!Between(p.x,line.a.x,line.b.x)||!Between(p.y,line.a.y,line.b.y))return false;
    const Vec3D da = line.a-p;
    const Vec3D db = line.b-p;
    return CosSquared(da,db)>1-EPSILON;
}
constexpr bool PointIn(const Vec2D& p, const Rect& rect)
{
    Rotate(p,rect.pos+rect.dim/2, -rect.angle);
    return PointIn(p,rect.box);
}
constexpr bool PointIn(const Vec3D& p, const Cube& rect)
{
    Rotate(p,rect.pos+rect.dim/2,-rect.alpha,-rect.beta,-rect.gamma);
    return PointIn(p,rect.box);
}
inline std::vector<Vec2D> ShapeOf(const Box2D& box)
{
 return {{box.x,box.y},{box.x+box.width,box.y},{box.x+box.width,box.y+box.height},{box.x,box.y+box.height}};
}
inline std::vector<Vec2D> ShapeOf(const Rect& rect)
{
    const std::vector<Vec2D> shape=ShapeOf(rect.box);
    const Vec2D center=rect.pos+rect.dim/2;
    return {{Rotate(shape[0],center,rect.angle)},{Rotate(shape[1],center,rect.angle)},{Rotate(shape[2],center,rect.angle)},{Rotate(shape[3],center,rect.angle)}};
}
inline std::vector<Vec2D> ShapeOf(const Circle& circle)
{
    const size_t n{static_cast<size_t>(circle.r/2)};
    const float interpolation{PI2/(n-1)};
        
    std::vector<Vec2D> retShape;

    for(size_t i=0; i<n;++i)retShape.push_back(circle.pos+PolarVec(interpolation*i)*circle.r);
    return retShape; 
}
inline std::vector<Vec2D> ShapeOf(const Polygon& polygon)
{
    const float interpolation{PI2/(polygon.n)};
        
    std::vector<Vec2D> retShape;

    for(size_t i=0; i<=polygon.n;++i)retShape.push_back(polygon.pos+PolarVec(interpolation*i+polygon.angle)*polygon.r);
    return retShape; 
}

inline std::vector<Vec2D> SampleFunction(const std::function<float(float)>& func, const float xStart, const float xEnd, const float step)
{
    std::vector<Vec2D> points;
    for(float x=xStart; x<xEnd;x+=step)
    points.push_back({x,func(x)});
    return points; 
}
inline std::vector<Vec2D> SampleParameterisation(const std::function<Vec2D(float)>& func, const float step)
{
    std::vector<Vec2D> points;
    for(float t=0; t<1;t+=step)
    points.push_back(func(t));

    return points; 
}

inline void InterMove(Ge::Vec2D& p, const Vec2D& endPoint,const float& speed=1, const float& dt=1)
{
    const float d=Squaredist(endPoint-p);
    if(d<10)return;
    p=p+(endPoint-p)*gcem::inv_sqrt(d)*speed*dt; 
}
//Interpolates between two Points with an t between 0 and 1 
constexpr Ge::Vec2D InterVec(const Ge::Vec2D& a, const Ge::Vec2D& b, const float& t)
{
    return a+(b-a)*t; 
}
//Interpolates between two Points with an t between 0 and 1 
constexpr Ge::Vec3D InterVec(const Ge::Vec3D& a, const Ge::Vec3D& b, const float& t)
{
    return a+(b-a)*t; 
}
//Interpolates between two functions with an t between 0 and 1 
template<class F, typename T>
constexpr F InterFunc(const F& f, const F& g, const T& x, const float& t)
{
    return f(x)+(g(x)-f(x))*t; 
} 





}
#endif