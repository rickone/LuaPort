#include "stdafx.h"
#include "LuaCastor.h"

LUA_PORT_NAMESPACE_BEGIN

Castor::Castor()
{

}

Castor::~Castor()
{

}

Castor* Castor::sharedLuaCastor()
{
    static Castor s_LuaCastor;
    return &s_LuaCastor;
}

void Castor::registerCastor(const char* pszClassFrom, const char* pszClassTo, CastorFunc pFunc)
{
    CastorList::iterator it = this->findCastorPair(pszClassFrom, pszClassTo);
    assert(it == mCastorList.end());

    CastorPair cPair;
    cPair.strFrom = pszClassFrom;
    cPair.strTo = pszClassTo;
    cPair.pCastor = pFunc;
    mCastorList.push_back(cPair);
}

void Castor::unregisterCastor(const char* pszClassFrom, const char* pszClassTo)
{
    CastorList::iterator it = this->findCastorPair(pszClassFrom, pszClassTo);
    assert(it != mCastorList.end());

    mCastorList.erase(it);
}

bool Castor::isRegistered(const char* pszClassFrom, const char* pszClassTo)
{
    CastorList::iterator it = this->findCastorPair(pszClassFrom, pszClassTo);

    return it != mCastorList.end();
}

void* Castor::castType(void* pvObj, const char* pszClassFrom, const char* pszClassTo)
{
    if (strcmp(pszClassFrom, pszClassTo) == 0)
        return pvObj;

    CastorList::iterator it = this->findCastorPair(pszClassFrom, pszClassTo);
    if (it != mCastorList.end())
    {
        return (*it->pCastor)(pvObj);
    }
    return NULL;
}

Castor::CastorList::iterator Castor::findCastorPair(const char* pszClassFrom, const char* pszClassTo)
{
    CastorList::iterator itEnd = mCastorList.end();
    for (CastorList::iterator it = mCastorList.begin(); it != itEnd; ++it)
    {
        if ((strcmp(it->strFrom.c_str(), pszClassFrom) == 0) && (strcmp(it->strTo.c_str(), pszClassTo) == 0))
        {
            return it;
        }
    }
    return itEnd;
}

LUA_PORT_NAMESPACE_END
