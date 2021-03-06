#ifndef ACTOR_H_
#define ACTOR_H_

#include "GameConstants.h"
#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor :public GraphObject {
    public:
        Actor(StudentWorld* studentWorld, int imageID, int startX, int startY, int dir, int depth, double size) 
        : m_studentWorld(studentWorld), 
        GraphObject(imageID, startX, startY, dir, depth, size), 
        m_alive(true)
        {}

        virtual ~Actor() {}
        virtual void isBonked() {}
        virtual void isDamaged() {}
        StudentWorld* getStudentWorld() { return m_studentWorld; }
        bool isAlive() { return m_alive; }
        void setDead() { m_alive = false; }
        virtual void doSomething() = 0;
        virtual bool isBlocking() {return false;}
        virtual bool isDamageable() {return false;}

    private:
        StudentWorld* m_studentWorld;
        bool m_alive; 

};  

class Peach :public Actor {
    public:
        Peach(StudentWorld* studentWorld, int startX, int startY)
        : Actor(studentWorld, IID_PEACH, startX, startY, 0, 0, 1.0),
         m_health(1), m_temporaryInvincibility(0), 
         m_starPower(0), m_shootPower(false), m_jumPower(false), 
         m_timeToRecharge(0), m_rJumpDistance(0), m_hitPoint(1)
          {}

        virtual ~Peach() {}
        virtual void isBonked();
        virtual void isDamaged();
        void gainPower(int type);
        void setHitPoint(int point);
        bool getStarPower() {return m_starPower>0;}
        bool getShootPower() {return m_shootPower;}
        bool getJumpPower() {return m_jumPower;}
        virtual bool isDamageable() {return true;}
        virtual void doSomething();
    private:
        int m_health;
        int m_temporaryInvincibility;
        int m_timeToRecharge;
        int m_starPower;
        bool m_shootPower;
        bool m_jumPower;
        int m_rJumpDistance;
        int m_hitPoint;
        /*
            noGoodie = 0
            starGoodie = 1 --> starPower
            flowerGoodie = 2 --> shootPower
            mushroomGoodie = 3 --> jumpPower
        */
};

class Fireball :public Actor {
    public:
        Fireball(StudentWorld* studentWorld, int imageID, int startX, int startY, int dir)
        : Actor(studentWorld, imageID, startX, startY, dir ,1, 1) 
        {}

        virtual ~Fireball() {}
        virtual void isBonked() {}
        virtual void doSomething() {}
        void helper();
    private:
    // kind: 0 --> peachFireball
    // kind: 1 --> piranhaFireball
};

class PeachFireball :public Fireball {
    public:
        PeachFireball(StudentWorld* studentWorld, int startX, int startY, int dir)
        : Fireball(studentWorld, IID_PEACH_FIRE, startX, startY, dir)
        {}

        virtual ~PeachFireball() {}
        virtual void doSomething();
    private:
};

class PiranhaFireball :public Fireball {
    public:
        PiranhaFireball(StudentWorld* studentWorld, int startX, int startY, int dir)
        : Fireball(studentWorld, IID_PIRANHA_FIRE, startX, startY, dir)
        {}

        virtual ~PiranhaFireball() {}
        virtual void doSomething();
    private:
};

class Shell :public Fireball {
    public: 
        Shell(StudentWorld* studentWorld, int startX, int startY, int dir)
        : Fireball(studentWorld, IID_SHELL, startX, startY, dir)
        {}
        virtual ~Shell() {}
        virtual void doSomething();
    private:
};

class BlockingObjects: public Actor {
    public:
        BlockingObjects(StudentWorld* studentWorld, int imageID ,int startX, int startY) 
        : Actor(studentWorld, imageID, startX, startY, 0, 2, 1)
        {}

        virtual ~BlockingObjects() {}
        virtual void isBonked();
        virtual void doSomething() {}
        virtual bool isBlocking() {return true;}

    private:
};

class Block :public BlockingObjects {    
    public:
        Block(StudentWorld* studentWorld, int startX, int startY, int goodie) 
        : BlockingObjects(studentWorld, IID_BLOCK, startX, startY),
        m_goodie(goodie) {}

        virtual ~Block() {}
        virtual void isBonked();
    private:
        /*
            noGoodie = 0
            starGoodie = 1
            flowerGoodie = 2
            mushroomGoodie = 3
        */
        int m_goodie;
};

class Pipe :public BlockingObjects {
    public:
        Pipe(StudentWorld* studentWorld, int startX, int startY) 
        : BlockingObjects(studentWorld, IID_PIPE, startX, startY)
        {}

        virtual ~Pipe() {}
    private:

};

class Goodie :public Actor {
    public:
        Goodie(StudentWorld* studentWorld, int imageID, int startX, int startY) 
        : Actor(studentWorld, imageID, startX, startY, 0, 1, 1)
        {}

        virtual ~Goodie() {}
        virtual void isBonked() {}
        virtual void doSomething() {}
        void helper();
    private:
    /*
            noGoodie = 0
            starGoodie = 1
            flowerGoodie = 2
            mushroomGoodie = 3
        */
};

class FlowerGoodie :public Goodie {
    public:
        FlowerGoodie(StudentWorld* studentWorld, int startX, int startY)
        : Goodie(studentWorld, IID_FLOWER, startX, startY)
        {}
        
        virtual ~FlowerGoodie() {}
        virtual void doSomething();

    private:
};

class MushroomGoodie :public Goodie {
    public:
        MushroomGoodie(StudentWorld* studentWorld, int startX, int startY)
        : Goodie(studentWorld, IID_MUSHROOM, startX, startY)
        {}
        
        virtual ~MushroomGoodie() {}
        virtual void doSomething();

    private:
};

class StarGoodie :public Goodie {
    public:
        StarGoodie(StudentWorld* studentWorld, int startX, int startY)
        : Goodie(studentWorld, IID_STAR, startX, startY)
        {}
        
        virtual ~StarGoodie() {}
        virtual void doSomething();

    private:
};

class Enemies :public Actor {
    public:
        Enemies(StudentWorld* studentWorld, int imageID ,int startX, int startY, int dir)
        : Actor(studentWorld, imageID, startX, startY, dir, 0, 1.0)
        {}

        virtual ~Enemies() {}
        virtual bool isDamageable() {return true;}
        virtual void doSomething();
        virtual void isBonked();
        virtual void isDamaged();
    private:
};

class Goomba :public Enemies {
    public:
        Goomba(StudentWorld* studentWorld, int startX, int startY, int dir)
        : Enemies(studentWorld, IID_GOOMBA, startX, startY, dir)
        {}

        virtual ~Goomba() {}
    private:
};

class Koopa :public Enemies {
    public:
        Koopa(StudentWorld* studentWorld, int startX, int startY, int dir)
        : Enemies(studentWorld, IID_KOOPA, startX, startY, dir)
        {}

        virtual ~Koopa() {}
        virtual void isBonked();
        virtual void isDamaged();
    private:
};

class Piranha :public Enemies {
    public:
        Piranha(StudentWorld* studentWorld, int startX, int startY, int dir)
         :Enemies(studentWorld, IID_PIRANHA, startX, startY, dir), m_firingDelay(0)
        {}
        virtual ~Piranha() {}
        virtual void doSomething();
    private:
        int m_firingDelay;
};

class Target :public Actor {
    public:
        Target(StudentWorld* studentWorld, int imageID, int startX, int startY)
        : Actor(studentWorld, imageID, startX, startY, 0, 1, 1)
        {}

        virtual ~Target() {}
        virtual void doSomething() {}
        virtual void isBonked() {}
        virtual void isDamaged() {}

    private:
};


class Flag :public Target {
    public:
        Flag(StudentWorld* studentWorld, int startX, int startY)
         :Target(studentWorld, IID_FLAG, startX, startY)
        {}

        virtual ~Flag() {}
        virtual void doSomething();
    private:

};

class Mario :public Target {
    public:
        Mario(StudentWorld* studentWorld, int startX, int startY)
        :Target(studentWorld, IID_MARIO, startX, startY)
        {}

        virtual ~Mario() {}
        virtual void doSomething();
};

#endif // ACTOR_H_
