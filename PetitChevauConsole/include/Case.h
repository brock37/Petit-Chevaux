#ifndef CASE_H
#define CASE_H



#include "constantes.h"

class Case
{
    public:
        /** Default constructor */
        Case();
        /** Default destructor */
        virtual ~Case();

        void setType(char n){ m_type= n;};
        char getType(){return m_type;};
    protected:
    private:
        char m_type;
        mon_array tab;

};

#endif // CASE_H
