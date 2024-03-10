#ifndef SIMPLERANDOM_HPP
#define SIMPLERANDOM_HPP
#include <ctime>

typedef struct simplerandom{
    unsigned long state = 1;
    unsigned oldstate = 3;
    time_t time = std::time(nullptr);

    simplerandom(unsigned long seed = 0){
        if(seed != 0){
            this->state = seed;
        } else {
            std::asctime(std::localtime(&this->time));
            this->state = (unsigned long)this->time;
        }
    }

    inline unsigned long Next(){
        this->oldstate = this->state;
        this->state = (48271 * this->state +1);

        return this->state;
    }

    inline unsigned long ScrambleNext(){
        this->oldstate = this->state;
        this->state = (this->state * this->state +1) / ((this->state)%(this->oldstate/48271));

        return this->state;
    }

    inline unsigned long RangedNext(unsigned long min, unsigned long max){
        unsigned long range = max-min+1;
        return (this->Next() % range) + min;
    }



} simplerandom;


#endif


