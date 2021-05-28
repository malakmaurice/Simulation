#include <iostream>
#include<fstream>
#include<string>
#include <stddef.h>
using namespace std;
class Node
{
    short Value;
    string Name;
public:
    void SetValue(short v)
    {
        Value=v;
    }
    short GetValue()
    {
        return Value;
    }

    void SetName(string n)
    {
        Name=n;
    }
    string GetName()
    {
        return Name;
    }
    void Print()
    {
        cout<<Name<<"  =  "<<Value<<endl;
    }
};
class Gate
{
protected:
    Node *In1;
    Node *In2;
    Node *Ou1;
public:
    void SetIn1(Node *n)
    {
        In1=n;
    }
    Node* GetIn1()
    {
        return In1;
    }
    void SetIn2(Node *n)
    {
        In2=n;
    }
    Node* GetIn2()
    {
        return In2;
    }
    void SetOu1(Node *n)
    {
        Ou1=n;
    }
    Node* GetOu1()
    {
        return Ou1;
    }
    virtual void Calculate()=0;
};
class AndGate:public Gate
{
public:
    void Calculate()
    {
        if(In1->GetValue()==1  && In2->GetValue() ==1)
            Ou1->SetValue(1);
        else
        {
            Ou1->SetValue(0);
        }
    }
};
class OrGate:public Gate
{
    void Calculate()
    {
        if(In1->GetValue()==1  || In2->GetValue() ==1)
            Ou1->SetValue(1);
        else
        {
            Ou1->SetValue(0);
        }
    }
};
class NandGate:public Gate
{
public:
    void Calculate()
    {
        if(In1->GetValue()==1  && In2->GetValue() ==1)
            Ou1->SetValue(0);
        else
        {
            Ou1->SetValue(1);
        }
    }
};
class XorGate:public Gate
{
public:
    void Calculate()
    {
        if(In1->GetValue()==In2->GetValue() )
            Ou1->SetValue(0);
        else
        {
            Ou1->SetValue(1);
        }
    }
};
class Simulator
{
    Gate* GA[1000];
    Node* NO[2000];
    int GateSize,NodeSize;
public:
    Simulator()
    {
        GateSize=0;
        NodeSize=0;
    }
    int GetNodeSize()
    {
        return NodeSize;
    }
    int GetGateSize()
    {
        return GateSize;
    }
    Node* FindNode(string n)
    {
        int i;
        for(i=0; i<GetNodeSize(); i++)
        {
            if(NO[i]->GetName()==n)
                return NO[i];
        }
        return NULL;
    }
    Node* AddNode(string n)
    {
        NO[NodeSize]=new Node();
        NO[NodeSize]->SetName(n);
        NodeSize++;
        return NO[NodeSize-1];
    }
    Node* FindAndAdd(string n)
    {
        Node*ptr=FindNode(n);
        if(ptr==NULL)
            ptr=AddNode(n);
        return ptr;
    }
    Gate* AddGate(string n)
    {
        if(n == "AND")
        {
            GA[GateSize]=new AndGate();
        }
        else if (n=="OR")
            GA[GateSize]=new OrGate();
        else if (n=="XOR")
            GA[GateSize]=new XorGate();
        else if (n=="NAND")
            GA[GateSize]=new NandGate();
        GateSize++;
        return GA[GateSize-1];
    }
    void Sim()
    {
        int i;
        for(i=0; i<GetGateSize(); i++)
            GA[i]->Calculate();
    }
    void PrintAllNodes()
    {
        int i;
        for(i=0;i<GetNodeSize();i++){
            NO[i]->Print();
        }
    }
void Load(const char * myfile)
    {
        ifstream f1;
        f1.open(myfile);
        while(!f1.eof())
        {
            string s;
            f1>>s;
            if(s=="SET")
            {
                string name;
                short value;
                f1>>name>>value;
                FindAndAdd(name)->SetValue(value);
            }
            else if(s=="SIM")
            {
                Sim();
            }
            else if(s=="OUT")
            {
                string n;
                f1>>n;
                if(n=="ALL")
                    PrintAllNodes();
                else
                {
                    FindAndAdd(n)->Print();
                }
            }
            else{
                Gate *ptr=AddGate(s);
                string n1,n2,n3;
                f1>>n1>>n2>>n3;
                ptr->SetIn1(FindAndAdd(n1));
                ptr->SetIn2(FindAndAdd(n2));
                ptr->SetOu1(FindAndAdd(n3));
            }
        }
    }
};
int main()
{
    Simulator s;
    s.Load("cir.txt");
    return 0;
}
