#ifndef CASE_H
#define CASE_H


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
};

#endif // CASE_H
