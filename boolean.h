#ifndef __BOOLEAN_H__
#define __BOOLEAN_H__

#include "object.h"

class Boolean : public Object {
public:

    Object *A;
    Object *B;
    enum Type {
        type_intersection, type_difference, type_union
    };
    Type type;

    Boolean(Object *a, Object *b, Type t)
            : type(t), A(a), B(b) {}

    virtual bool Intersection(const Ray &ray, std::vector<Hit> &hits) const override;

    virtual vec3 Normal(const vec3 &point, int part) const override;

    virtual bool isInside(const vec3 &point) override;
};

#endif
