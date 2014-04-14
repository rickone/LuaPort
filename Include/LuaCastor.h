#pragma once

LUA_PORT_NAMESPACE_BEGIN

typedef void* (*CastorFunc)(void*);

class Castor
{
public:
    Castor();
    virtual ~Castor();

    static Castor* sharedLuaCastor();
    void registerCastor(const char* pszClassFrom, const char* pszClassTo, CastorFunc pFunc);
    void unregisterCastor(const char* pszClassFrom, const char* pszClassTo);
    bool isRegistered(const char* pszClassFrom, const char* pszClassTo);
    void* castType(void* pvObj, const char* pszClassFrom, const char* pszClassTo);

private:
    struct CastorPair 
    {
        std::string     strFrom;
        std::string     strTo;
        CastorFunc   pCastor;
    };

    typedef std::list<CastorPair> CastorList;
    CastorList mCastorList;

    CastorList::iterator findCastorPair(const char* pszClassFrom, const char* pszClassTo);
};

template<typename Src, typename Dst>
class TemplateCastor
{
public:
    static void* StaticCastor(void* pvObj)
    {
        Src* pSrcObj = static_cast<Src*>(pvObj);
        Dst* pDstObj = static_cast<Dst*>(pSrcObj);
        return pDstObj;
    }

    static void* DynamicCastor(void* pvObj)
    {
        Src* pSrcObj = static_cast<Src*>(pvObj);
        Dst* pDstObj = dynamic_cast<Dst*>(pSrcObj);
        return pDstObj;
    }
};

LUA_PORT_NAMESPACE_END
