#include "TPlex.h"
#include "Stack.h"

TPlex::TPlex()
{
    left = new TPoint();
    right = new TPoint();
}

TPlex::TPlex(TPoint* a, TPoint* b)
{
    if (a != NULL)
        left = a;
    if (b != NULL)
        right = b;
}

TPlex::TPlex(const TPlex& p)
{
    left = p.left->Clone();
    right = p.right->Clone();
}

void TPlex::Print()
{
    PrintAll();
}

double TPlex::GetVal(int i)
{
    throw new exception;
}

double TPlex::SetVal(double val, int i)
{
    throw new exception;
}

double& TPlex::operator[](char* name)
{
    throw new exception;
}

double& TPlex::operator[](int i)
{
    throw new exception;
}

TBase* TPlex::GetChild(int i)
{
    if (i == 0)
        return left;
    else if (i == 1)
        return right;
    else
        throw new exception;
}

void TPlex::SetChild(TBase* c, int i)
{
    if (i == 0)
        left = c;
    else if (i == 1)
        right = c;
    else
        throw new exception;
}

TBase* TPlex::PrintAll()
{
    std::cout << *this << "\n";
    return 0;
}

TBase* TPlex::GetLeft()
{
    return left;
}

TBase* TPlex::GetRight()
{
    return right;
}

TPlex* TPlex::GetLeftPlex()
{
    return dynamic_cast<TPlex*>(left);
}

TPlex* TPlex::GetRightPlex()
{
    return dynamic_cast<TPlex*>(right);
}

void TPlex::SetLeft(TBase* x)
{
    left = x;
}

void TPlex::SetRight(TBase* x)
{
    right = x;
}

bool TPlex::AddLine(TPoint* a, TPoint* b)
{
    TStack<TBase*> stack(100);
    stack.Push(this);
    bool res = false;

    while (!stack.IsEmpty())
    {
        TBase* top = stack.Get();
        TBase* right = top->GetChild(0);
        TBase* left = top->GetChild(1);

        if (right->GetChildCount() != 0)
            stack.Push(right);
        else if (right == a)
        {
            TPlex* _plex = new TPlex(a, b);
            top->SetChild(_plex, 0);
            res = true;
            break;
        }
        if (left->GetChildCount() != 0)
            stack.Push(left);
        else if (left == b)
        {
            TPlex* _plex = new TPlex(b, a);
            top->SetChild(_plex, 1);
            res = true;
            break;
        }
    }
    return res;
}

TBase* TPlex::Clone()
{
    return new TPlex(*this);
}

std::ostream& operator<<(std::ostream& out, const TPlex& _plex)
{
    TBase* base = const_cast<TPlex*>(&_plex);
    TPoint* firstPoint = NULL;
    TPoint* lastPoint = NULL;
    TStack<TBase*> stack(100);
    stack.Push(base);

    while (!stack.IsEmpty())
    {
        base = stack.Get();

        while (firstPoint == NULL)
        {
            TBase* leftBase = base->GetChild(0);
            TPlex* plex = dynamic_cast<TPlex*>(leftBase);
            if (plex == NULL)
                firstPoint = dynamic_cast<TPoint*>(leftBase);
            else
            {
                stack.Push(base);
                base = leftBase;
            }
        }

        while (lastPoint == NULL)
        {
            TBase* rightBase = base->GetChild(0);
            TPlex* plex = dynamic_cast<TPlex*>(rightBase);

            if (plex == NULL)
                lastPoint = dynamic_cast<TPoint*>(rightBase);
            else
            {
                stack.Push(base);
                base = rightBase;
            }
        }

        if (firstPoint != NULL && lastPoint != NULL)
        {
            TLine line(*firstPoint, *lastPoint);
            out << line << "\n";
            TBase* tbase = lastPoint;
            if (!stack.IsEmpty())
            {
                base = stack.Get();
                TBase* leftBase = base->GetChild(0);
                TBase* rightBase = base->GetChild(1);

                TPlex* leftPlex = dynamic_cast<TPlex*>(leftBase);
                TPlex* rightPlex = dynamic_cast<TPlex*>(rightBase);

                if (leftPlex != NULL && rightPlex != NULL)
                {
                    TPlex* nplex = new TPlex(lastPoint, 0);
                    nplex->SetChild(rightBase, 1);
                    stack.Push(nplex);
                    lastPoint = NULL;
                    firstPoint = NULL;
                }
                else
                {
                    if (leftPlex != NULL)
                    {
                        firstPoint = dynamic_cast<TPoint*>(tbase);
                        lastPoint = NULL;
                    }
                    else
                    {
                        lastPoint = dynamic_cast<TPoint*>(tbase);
                        firstPoint = NULL;
                    }
                    stack.Push(base);
                }
            }
        }
    }
    return out;
}