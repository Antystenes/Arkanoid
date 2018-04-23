#ifndef MOVABLE_H
#define MOVABLE_H


class Movable
{
    public:
        Movable() = default;
        virtual ~Movable() = default;
        virtual void Move(float, float) = 0;
    protected:

    private:
};

#endif // MOVABLE_H
