//
// Generated file, do not edit! Created by opp_msgtool 6.2 from DroneAuthMessages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "DroneAuthMessages_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(AuthCommit)

AuthCommit::AuthCommit(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

AuthCommit::AuthCommit(const AuthCommit& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

AuthCommit::~AuthCommit()
{
}

AuthCommit& AuthCommit::operator=(const AuthCommit& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void AuthCommit::copy(const AuthCommit& other)
{
    this->droneId = other.droneId;
    this->commitment = other.commitment;
    this->timestamp = other.timestamp;
}

void AuthCommit::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->droneId);
    doParsimPacking(b,this->commitment);
    doParsimPacking(b,this->timestamp);
}

void AuthCommit::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->droneId);
    doParsimUnpacking(b,this->commitment);
    doParsimUnpacking(b,this->timestamp);
}

int AuthCommit::getDroneId() const
{
    return this->droneId;
}

void AuthCommit::setDroneId(int droneId)
{
    this->droneId = droneId;
}

const char * AuthCommit::getCommitment() const
{
    return this->commitment.c_str();
}

void AuthCommit::setCommitment(const char * commitment)
{
    this->commitment = commitment;
}

omnetpp::simtime_t AuthCommit::getTimestamp() const
{
    return this->timestamp;
}

void AuthCommit::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

class AuthCommitDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_droneId,
        FIELD_commitment,
        FIELD_timestamp,
    };
  public:
    AuthCommitDescriptor();
    virtual ~AuthCommitDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(AuthCommitDescriptor)

AuthCommitDescriptor::AuthCommitDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(AuthCommit)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

AuthCommitDescriptor::~AuthCommitDescriptor()
{
    delete[] propertyNames;
}

bool AuthCommitDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AuthCommit *>(obj)!=nullptr;
}

const char **AuthCommitDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AuthCommitDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AuthCommitDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int AuthCommitDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_droneId
        FD_ISEDITABLE,    // FIELD_commitment
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *AuthCommitDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "droneId",
        "commitment",
        "timestamp",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int AuthCommitDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "droneId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "commitment") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *AuthCommitDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_droneId
        "string",    // FIELD_commitment
        "omnetpp::simtime_t",    // FIELD_timestamp
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **AuthCommitDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AuthCommitDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AuthCommitDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AuthCommit *pp = omnetpp::fromAnyPtr<AuthCommit>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AuthCommitDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthCommit *pp = omnetpp::fromAnyPtr<AuthCommit>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AuthCommit'", field);
    }
}

const char *AuthCommitDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AuthCommit *pp = omnetpp::fromAnyPtr<AuthCommit>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AuthCommitDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AuthCommit *pp = omnetpp::fromAnyPtr<AuthCommit>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: return long2string(pp->getDroneId());
        case FIELD_commitment: return oppstring2string(pp->getCommitment());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        default: return "";
    }
}

void AuthCommitDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthCommit *pp = omnetpp::fromAnyPtr<AuthCommit>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: pp->setDroneId(string2long(value)); break;
        case FIELD_commitment: pp->setCommitment((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AuthCommit'", field);
    }
}

omnetpp::cValue AuthCommitDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AuthCommit *pp = omnetpp::fromAnyPtr<AuthCommit>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: return pp->getDroneId();
        case FIELD_commitment: return pp->getCommitment();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AuthCommit' as cValue -- field index out of range?", field);
    }
}

void AuthCommitDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthCommit *pp = omnetpp::fromAnyPtr<AuthCommit>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: pp->setDroneId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_commitment: pp->setCommitment(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AuthCommit'", field);
    }
}

const char *AuthCommitDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr AuthCommitDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AuthCommit *pp = omnetpp::fromAnyPtr<AuthCommit>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AuthCommitDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthCommit *pp = omnetpp::fromAnyPtr<AuthCommit>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AuthCommit'", field);
    }
}

Register_Class(AuthChallenge)

AuthChallenge::AuthChallenge(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

AuthChallenge::AuthChallenge(const AuthChallenge& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

AuthChallenge::~AuthChallenge()
{
}

AuthChallenge& AuthChallenge::operator=(const AuthChallenge& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void AuthChallenge::copy(const AuthChallenge& other)
{
    this->droneId = other.droneId;
    this->challenge = other.challenge;
    this->timestamp = other.timestamp;
}

void AuthChallenge::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->droneId);
    doParsimPacking(b,this->challenge);
    doParsimPacking(b,this->timestamp);
}

void AuthChallenge::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->droneId);
    doParsimUnpacking(b,this->challenge);
    doParsimUnpacking(b,this->timestamp);
}

int AuthChallenge::getDroneId() const
{
    return this->droneId;
}

void AuthChallenge::setDroneId(int droneId)
{
    this->droneId = droneId;
}

const char * AuthChallenge::getChallenge() const
{
    return this->challenge.c_str();
}

void AuthChallenge::setChallenge(const char * challenge)
{
    this->challenge = challenge;
}

omnetpp::simtime_t AuthChallenge::getTimestamp() const
{
    return this->timestamp;
}

void AuthChallenge::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

class AuthChallengeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_droneId,
        FIELD_challenge,
        FIELD_timestamp,
    };
  public:
    AuthChallengeDescriptor();
    virtual ~AuthChallengeDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(AuthChallengeDescriptor)

AuthChallengeDescriptor::AuthChallengeDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(AuthChallenge)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

AuthChallengeDescriptor::~AuthChallengeDescriptor()
{
    delete[] propertyNames;
}

bool AuthChallengeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AuthChallenge *>(obj)!=nullptr;
}

const char **AuthChallengeDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AuthChallengeDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AuthChallengeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int AuthChallengeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_droneId
        FD_ISEDITABLE,    // FIELD_challenge
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *AuthChallengeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "droneId",
        "challenge",
        "timestamp",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int AuthChallengeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "droneId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "challenge") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *AuthChallengeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_droneId
        "string",    // FIELD_challenge
        "omnetpp::simtime_t",    // FIELD_timestamp
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **AuthChallengeDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AuthChallengeDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AuthChallengeDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AuthChallenge *pp = omnetpp::fromAnyPtr<AuthChallenge>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AuthChallengeDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthChallenge *pp = omnetpp::fromAnyPtr<AuthChallenge>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AuthChallenge'", field);
    }
}

const char *AuthChallengeDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AuthChallenge *pp = omnetpp::fromAnyPtr<AuthChallenge>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AuthChallengeDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AuthChallenge *pp = omnetpp::fromAnyPtr<AuthChallenge>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: return long2string(pp->getDroneId());
        case FIELD_challenge: return oppstring2string(pp->getChallenge());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        default: return "";
    }
}

void AuthChallengeDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthChallenge *pp = omnetpp::fromAnyPtr<AuthChallenge>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: pp->setDroneId(string2long(value)); break;
        case FIELD_challenge: pp->setChallenge((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AuthChallenge'", field);
    }
}

omnetpp::cValue AuthChallengeDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AuthChallenge *pp = omnetpp::fromAnyPtr<AuthChallenge>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: return pp->getDroneId();
        case FIELD_challenge: return pp->getChallenge();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AuthChallenge' as cValue -- field index out of range?", field);
    }
}

void AuthChallengeDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthChallenge *pp = omnetpp::fromAnyPtr<AuthChallenge>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: pp->setDroneId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_challenge: pp->setChallenge(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AuthChallenge'", field);
    }
}

const char *AuthChallengeDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr AuthChallengeDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AuthChallenge *pp = omnetpp::fromAnyPtr<AuthChallenge>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AuthChallengeDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthChallenge *pp = omnetpp::fromAnyPtr<AuthChallenge>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AuthChallenge'", field);
    }
}

Register_Class(AuthResponse)

AuthResponse::AuthResponse(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

AuthResponse::AuthResponse(const AuthResponse& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

AuthResponse::~AuthResponse()
{
}

AuthResponse& AuthResponse::operator=(const AuthResponse& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void AuthResponse::copy(const AuthResponse& other)
{
    this->droneId = other.droneId;
    this->response = other.response;
    this->timestamp = other.timestamp;
}

void AuthResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->droneId);
    doParsimPacking(b,this->response);
    doParsimPacking(b,this->timestamp);
}

void AuthResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->droneId);
    doParsimUnpacking(b,this->response);
    doParsimUnpacking(b,this->timestamp);
}

int AuthResponse::getDroneId() const
{
    return this->droneId;
}

void AuthResponse::setDroneId(int droneId)
{
    this->droneId = droneId;
}

const char * AuthResponse::getResponse() const
{
    return this->response.c_str();
}

void AuthResponse::setResponse(const char * response)
{
    this->response = response;
}

omnetpp::simtime_t AuthResponse::getTimestamp() const
{
    return this->timestamp;
}

void AuthResponse::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

class AuthResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_droneId,
        FIELD_response,
        FIELD_timestamp,
    };
  public:
    AuthResponseDescriptor();
    virtual ~AuthResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(AuthResponseDescriptor)

AuthResponseDescriptor::AuthResponseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(AuthResponse)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

AuthResponseDescriptor::~AuthResponseDescriptor()
{
    delete[] propertyNames;
}

bool AuthResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AuthResponse *>(obj)!=nullptr;
}

const char **AuthResponseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AuthResponseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AuthResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int AuthResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_droneId
        FD_ISEDITABLE,    // FIELD_response
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *AuthResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "droneId",
        "response",
        "timestamp",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int AuthResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "droneId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "response") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *AuthResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_droneId
        "string",    // FIELD_response
        "omnetpp::simtime_t",    // FIELD_timestamp
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **AuthResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AuthResponseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AuthResponseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AuthResponse *pp = omnetpp::fromAnyPtr<AuthResponse>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AuthResponseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthResponse *pp = omnetpp::fromAnyPtr<AuthResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AuthResponse'", field);
    }
}

const char *AuthResponseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AuthResponse *pp = omnetpp::fromAnyPtr<AuthResponse>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AuthResponseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AuthResponse *pp = omnetpp::fromAnyPtr<AuthResponse>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: return long2string(pp->getDroneId());
        case FIELD_response: return oppstring2string(pp->getResponse());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        default: return "";
    }
}

void AuthResponseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthResponse *pp = omnetpp::fromAnyPtr<AuthResponse>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: pp->setDroneId(string2long(value)); break;
        case FIELD_response: pp->setResponse((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AuthResponse'", field);
    }
}

omnetpp::cValue AuthResponseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AuthResponse *pp = omnetpp::fromAnyPtr<AuthResponse>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: return pp->getDroneId();
        case FIELD_response: return pp->getResponse();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AuthResponse' as cValue -- field index out of range?", field);
    }
}

void AuthResponseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthResponse *pp = omnetpp::fromAnyPtr<AuthResponse>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: pp->setDroneId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_response: pp->setResponse(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AuthResponse'", field);
    }
}

const char *AuthResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr AuthResponseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AuthResponse *pp = omnetpp::fromAnyPtr<AuthResponse>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AuthResponseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthResponse *pp = omnetpp::fromAnyPtr<AuthResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AuthResponse'", field);
    }
}

Register_Class(AuthResult)

AuthResult::AuthResult(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

AuthResult::AuthResult(const AuthResult& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

AuthResult::~AuthResult()
{
}

AuthResult& AuthResult::operator=(const AuthResult& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void AuthResult::copy(const AuthResult& other)
{
    this->droneId = other.droneId;
    this->authenticated = other.authenticated;
    this->reason = other.reason;
    this->timestamp = other.timestamp;
}

void AuthResult::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->droneId);
    doParsimPacking(b,this->authenticated);
    doParsimPacking(b,this->reason);
    doParsimPacking(b,this->timestamp);
}

void AuthResult::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->droneId);
    doParsimUnpacking(b,this->authenticated);
    doParsimUnpacking(b,this->reason);
    doParsimUnpacking(b,this->timestamp);
}

int AuthResult::getDroneId() const
{
    return this->droneId;
}

void AuthResult::setDroneId(int droneId)
{
    this->droneId = droneId;
}

bool AuthResult::getAuthenticated() const
{
    return this->authenticated;
}

void AuthResult::setAuthenticated(bool authenticated)
{
    this->authenticated = authenticated;
}

const char * AuthResult::getReason() const
{
    return this->reason.c_str();
}

void AuthResult::setReason(const char * reason)
{
    this->reason = reason;
}

omnetpp::simtime_t AuthResult::getTimestamp() const
{
    return this->timestamp;
}

void AuthResult::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

class AuthResultDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_droneId,
        FIELD_authenticated,
        FIELD_reason,
        FIELD_timestamp,
    };
  public:
    AuthResultDescriptor();
    virtual ~AuthResultDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(AuthResultDescriptor)

AuthResultDescriptor::AuthResultDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(AuthResult)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

AuthResultDescriptor::~AuthResultDescriptor()
{
    delete[] propertyNames;
}

bool AuthResultDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AuthResult *>(obj)!=nullptr;
}

const char **AuthResultDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AuthResultDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AuthResultDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int AuthResultDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_droneId
        FD_ISEDITABLE,    // FIELD_authenticated
        FD_ISEDITABLE,    // FIELD_reason
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *AuthResultDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "droneId",
        "authenticated",
        "reason",
        "timestamp",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int AuthResultDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "droneId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "authenticated") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "reason") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *AuthResultDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_droneId
        "bool",    // FIELD_authenticated
        "string",    // FIELD_reason
        "omnetpp::simtime_t",    // FIELD_timestamp
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **AuthResultDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AuthResultDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AuthResultDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AuthResult *pp = omnetpp::fromAnyPtr<AuthResult>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AuthResultDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthResult *pp = omnetpp::fromAnyPtr<AuthResult>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AuthResult'", field);
    }
}

const char *AuthResultDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AuthResult *pp = omnetpp::fromAnyPtr<AuthResult>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AuthResultDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AuthResult *pp = omnetpp::fromAnyPtr<AuthResult>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: return long2string(pp->getDroneId());
        case FIELD_authenticated: return bool2string(pp->getAuthenticated());
        case FIELD_reason: return oppstring2string(pp->getReason());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        default: return "";
    }
}

void AuthResultDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthResult *pp = omnetpp::fromAnyPtr<AuthResult>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: pp->setDroneId(string2long(value)); break;
        case FIELD_authenticated: pp->setAuthenticated(string2bool(value)); break;
        case FIELD_reason: pp->setReason((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AuthResult'", field);
    }
}

omnetpp::cValue AuthResultDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AuthResult *pp = omnetpp::fromAnyPtr<AuthResult>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: return pp->getDroneId();
        case FIELD_authenticated: return pp->getAuthenticated();
        case FIELD_reason: return pp->getReason();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AuthResult' as cValue -- field index out of range?", field);
    }
}

void AuthResultDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthResult *pp = omnetpp::fromAnyPtr<AuthResult>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: pp->setDroneId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_authenticated: pp->setAuthenticated(value.boolValue()); break;
        case FIELD_reason: pp->setReason(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AuthResult'", field);
    }
}

const char *AuthResultDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr AuthResultDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AuthResult *pp = omnetpp::fromAnyPtr<AuthResult>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AuthResultDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AuthResult *pp = omnetpp::fromAnyPtr<AuthResult>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AuthResult'", field);
    }
}

Register_Class(HeartbeatMessage)

HeartbeatMessage::HeartbeatMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

HeartbeatMessage::HeartbeatMessage(const HeartbeatMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

HeartbeatMessage::~HeartbeatMessage()
{
}

HeartbeatMessage& HeartbeatMessage::operator=(const HeartbeatMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void HeartbeatMessage::copy(const HeartbeatMessage& other)
{
    this->senderGCS = other.senderGCS;
    this->timestamp = other.timestamp;
    this->status = other.status;
    this->activeDrones = other.activeDrones;
}

void HeartbeatMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->senderGCS);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->status);
    doParsimPacking(b,this->activeDrones);
}

void HeartbeatMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->senderGCS);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->status);
    doParsimUnpacking(b,this->activeDrones);
}

const char * HeartbeatMessage::getSenderGCS() const
{
    return this->senderGCS.c_str();
}

void HeartbeatMessage::setSenderGCS(const char * senderGCS)
{
    this->senderGCS = senderGCS;
}

omnetpp::simtime_t HeartbeatMessage::getTimestamp() const
{
    return this->timestamp;
}

void HeartbeatMessage::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

const char * HeartbeatMessage::getStatus() const
{
    return this->status.c_str();
}

void HeartbeatMessage::setStatus(const char * status)
{
    this->status = status;
}

int HeartbeatMessage::getActiveDrones() const
{
    return this->activeDrones;
}

void HeartbeatMessage::setActiveDrones(int activeDrones)
{
    this->activeDrones = activeDrones;
}

class HeartbeatMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_senderGCS,
        FIELD_timestamp,
        FIELD_status,
        FIELD_activeDrones,
    };
  public:
    HeartbeatMessageDescriptor();
    virtual ~HeartbeatMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(HeartbeatMessageDescriptor)

HeartbeatMessageDescriptor::HeartbeatMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(HeartbeatMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

HeartbeatMessageDescriptor::~HeartbeatMessageDescriptor()
{
    delete[] propertyNames;
}

bool HeartbeatMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HeartbeatMessage *>(obj)!=nullptr;
}

const char **HeartbeatMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HeartbeatMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HeartbeatMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int HeartbeatMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_senderGCS
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_status
        FD_ISEDITABLE,    // FIELD_activeDrones
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *HeartbeatMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderGCS",
        "timestamp",
        "status",
        "activeDrones",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int HeartbeatMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "senderGCS") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "status") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "activeDrones") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *HeartbeatMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_senderGCS
        "omnetpp::simtime_t",    // FIELD_timestamp
        "string",    // FIELD_status
        "int",    // FIELD_activeDrones
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **HeartbeatMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *HeartbeatMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int HeartbeatMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HeartbeatMessage *pp = omnetpp::fromAnyPtr<HeartbeatMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HeartbeatMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HeartbeatMessage *pp = omnetpp::fromAnyPtr<HeartbeatMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HeartbeatMessage'", field);
    }
}

const char *HeartbeatMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HeartbeatMessage *pp = omnetpp::fromAnyPtr<HeartbeatMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HeartbeatMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HeartbeatMessage *pp = omnetpp::fromAnyPtr<HeartbeatMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderGCS: return oppstring2string(pp->getSenderGCS());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        case FIELD_status: return oppstring2string(pp->getStatus());
        case FIELD_activeDrones: return long2string(pp->getActiveDrones());
        default: return "";
    }
}

void HeartbeatMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HeartbeatMessage *pp = omnetpp::fromAnyPtr<HeartbeatMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderGCS: pp->setSenderGCS((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        case FIELD_status: pp->setStatus((value)); break;
        case FIELD_activeDrones: pp->setActiveDrones(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HeartbeatMessage'", field);
    }
}

omnetpp::cValue HeartbeatMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HeartbeatMessage *pp = omnetpp::fromAnyPtr<HeartbeatMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderGCS: return pp->getSenderGCS();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        case FIELD_status: return pp->getStatus();
        case FIELD_activeDrones: return pp->getActiveDrones();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HeartbeatMessage' as cValue -- field index out of range?", field);
    }
}

void HeartbeatMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HeartbeatMessage *pp = omnetpp::fromAnyPtr<HeartbeatMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderGCS: pp->setSenderGCS(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_status: pp->setStatus(value.stringValue()); break;
        case FIELD_activeDrones: pp->setActiveDrones(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HeartbeatMessage'", field);
    }
}

const char *HeartbeatMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr HeartbeatMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HeartbeatMessage *pp = omnetpp::fromAnyPtr<HeartbeatMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HeartbeatMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HeartbeatMessage *pp = omnetpp::fromAnyPtr<HeartbeatMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HeartbeatMessage'", field);
    }
}

Register_Class(StateSyncMessage)

StateSyncMessage::StateSyncMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

StateSyncMessage::StateSyncMessage(const StateSyncMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

StateSyncMessage::~StateSyncMessage()
{
}

StateSyncMessage& StateSyncMessage::operator=(const StateSyncMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void StateSyncMessage::copy(const StateSyncMessage& other)
{
    this->droneId = other.droneId;
    this->authenticated = other.authenticated;
    this->commitment = other.commitment;
    this->publicKey = other.publicKey;
    this->lastAuthTime = other.lastAuthTime;
    this->authCount = other.authCount;
    this->fullSync = other.fullSync;
}

void StateSyncMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->droneId);
    doParsimPacking(b,this->authenticated);
    doParsimPacking(b,this->commitment);
    doParsimPacking(b,this->publicKey);
    doParsimPacking(b,this->lastAuthTime);
    doParsimPacking(b,this->authCount);
    doParsimPacking(b,this->fullSync);
}

void StateSyncMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->droneId);
    doParsimUnpacking(b,this->authenticated);
    doParsimUnpacking(b,this->commitment);
    doParsimUnpacking(b,this->publicKey);
    doParsimUnpacking(b,this->lastAuthTime);
    doParsimUnpacking(b,this->authCount);
    doParsimUnpacking(b,this->fullSync);
}

int StateSyncMessage::getDroneId() const
{
    return this->droneId;
}

void StateSyncMessage::setDroneId(int droneId)
{
    this->droneId = droneId;
}

bool StateSyncMessage::getAuthenticated() const
{
    return this->authenticated;
}

void StateSyncMessage::setAuthenticated(bool authenticated)
{
    this->authenticated = authenticated;
}

const char * StateSyncMessage::getCommitment() const
{
    return this->commitment.c_str();
}

void StateSyncMessage::setCommitment(const char * commitment)
{
    this->commitment = commitment;
}

long StateSyncMessage::getPublicKey() const
{
    return this->publicKey;
}

void StateSyncMessage::setPublicKey(long publicKey)
{
    this->publicKey = publicKey;
}

omnetpp::simtime_t StateSyncMessage::getLastAuthTime() const
{
    return this->lastAuthTime;
}

void StateSyncMessage::setLastAuthTime(omnetpp::simtime_t lastAuthTime)
{
    this->lastAuthTime = lastAuthTime;
}

int StateSyncMessage::getAuthCount() const
{
    return this->authCount;
}

void StateSyncMessage::setAuthCount(int authCount)
{
    this->authCount = authCount;
}

bool StateSyncMessage::getFullSync() const
{
    return this->fullSync;
}

void StateSyncMessage::setFullSync(bool fullSync)
{
    this->fullSync = fullSync;
}

class StateSyncMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_droneId,
        FIELD_authenticated,
        FIELD_commitment,
        FIELD_publicKey,
        FIELD_lastAuthTime,
        FIELD_authCount,
        FIELD_fullSync,
    };
  public:
    StateSyncMessageDescriptor();
    virtual ~StateSyncMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(StateSyncMessageDescriptor)

StateSyncMessageDescriptor::StateSyncMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(StateSyncMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

StateSyncMessageDescriptor::~StateSyncMessageDescriptor()
{
    delete[] propertyNames;
}

bool StateSyncMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<StateSyncMessage *>(obj)!=nullptr;
}

const char **StateSyncMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *StateSyncMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int StateSyncMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int StateSyncMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_droneId
        FD_ISEDITABLE,    // FIELD_authenticated
        FD_ISEDITABLE,    // FIELD_commitment
        FD_ISEDITABLE,    // FIELD_publicKey
        FD_ISEDITABLE,    // FIELD_lastAuthTime
        FD_ISEDITABLE,    // FIELD_authCount
        FD_ISEDITABLE,    // FIELD_fullSync
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *StateSyncMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "droneId",
        "authenticated",
        "commitment",
        "publicKey",
        "lastAuthTime",
        "authCount",
        "fullSync",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int StateSyncMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "droneId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "authenticated") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "commitment") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "publicKey") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "lastAuthTime") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "authCount") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "fullSync") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *StateSyncMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_droneId
        "bool",    // FIELD_authenticated
        "string",    // FIELD_commitment
        "long",    // FIELD_publicKey
        "omnetpp::simtime_t",    // FIELD_lastAuthTime
        "int",    // FIELD_authCount
        "bool",    // FIELD_fullSync
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **StateSyncMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *StateSyncMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int StateSyncMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    StateSyncMessage *pp = omnetpp::fromAnyPtr<StateSyncMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void StateSyncMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    StateSyncMessage *pp = omnetpp::fromAnyPtr<StateSyncMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'StateSyncMessage'", field);
    }
}

const char *StateSyncMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    StateSyncMessage *pp = omnetpp::fromAnyPtr<StateSyncMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string StateSyncMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    StateSyncMessage *pp = omnetpp::fromAnyPtr<StateSyncMessage>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: return long2string(pp->getDroneId());
        case FIELD_authenticated: return bool2string(pp->getAuthenticated());
        case FIELD_commitment: return oppstring2string(pp->getCommitment());
        case FIELD_publicKey: return long2string(pp->getPublicKey());
        case FIELD_lastAuthTime: return simtime2string(pp->getLastAuthTime());
        case FIELD_authCount: return long2string(pp->getAuthCount());
        case FIELD_fullSync: return bool2string(pp->getFullSync());
        default: return "";
    }
}

void StateSyncMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    StateSyncMessage *pp = omnetpp::fromAnyPtr<StateSyncMessage>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: pp->setDroneId(string2long(value)); break;
        case FIELD_authenticated: pp->setAuthenticated(string2bool(value)); break;
        case FIELD_commitment: pp->setCommitment((value)); break;
        case FIELD_publicKey: pp->setPublicKey(string2long(value)); break;
        case FIELD_lastAuthTime: pp->setLastAuthTime(string2simtime(value)); break;
        case FIELD_authCount: pp->setAuthCount(string2long(value)); break;
        case FIELD_fullSync: pp->setFullSync(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'StateSyncMessage'", field);
    }
}

omnetpp::cValue StateSyncMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    StateSyncMessage *pp = omnetpp::fromAnyPtr<StateSyncMessage>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: return pp->getDroneId();
        case FIELD_authenticated: return pp->getAuthenticated();
        case FIELD_commitment: return pp->getCommitment();
        case FIELD_publicKey: return (omnetpp::intval_t)(pp->getPublicKey());
        case FIELD_lastAuthTime: return pp->getLastAuthTime().dbl();
        case FIELD_authCount: return pp->getAuthCount();
        case FIELD_fullSync: return pp->getFullSync();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'StateSyncMessage' as cValue -- field index out of range?", field);
    }
}

void StateSyncMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    StateSyncMessage *pp = omnetpp::fromAnyPtr<StateSyncMessage>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: pp->setDroneId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_authenticated: pp->setAuthenticated(value.boolValue()); break;
        case FIELD_commitment: pp->setCommitment(value.stringValue()); break;
        case FIELD_publicKey: pp->setPublicKey(omnetpp::checked_int_cast<long>(value.intValue())); break;
        case FIELD_lastAuthTime: pp->setLastAuthTime(value.doubleValue()); break;
        case FIELD_authCount: pp->setAuthCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_fullSync: pp->setFullSync(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'StateSyncMessage'", field);
    }
}

const char *StateSyncMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr StateSyncMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    StateSyncMessage *pp = omnetpp::fromAnyPtr<StateSyncMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void StateSyncMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    StateSyncMessage *pp = omnetpp::fromAnyPtr<StateSyncMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'StateSyncMessage'", field);
    }
}

Register_Class(GCSAnnouncementMessage)

GCSAnnouncementMessage::GCSAnnouncementMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

GCSAnnouncementMessage::GCSAnnouncementMessage(const GCSAnnouncementMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

GCSAnnouncementMessage::~GCSAnnouncementMessage()
{
}

GCSAnnouncementMessage& GCSAnnouncementMessage::operator=(const GCSAnnouncementMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void GCSAnnouncementMessage::copy(const GCSAnnouncementMessage& other)
{
    this->newPrimaryAddress = other.newPrimaryAddress;
    this->reason = other.reason;
    this->timestamp = other.timestamp;
    this->droneCount = other.droneCount;
}

void GCSAnnouncementMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->newPrimaryAddress);
    doParsimPacking(b,this->reason);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->droneCount);
}

void GCSAnnouncementMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->newPrimaryAddress);
    doParsimUnpacking(b,this->reason);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->droneCount);
}

const char * GCSAnnouncementMessage::getNewPrimaryAddress() const
{
    return this->newPrimaryAddress.c_str();
}

void GCSAnnouncementMessage::setNewPrimaryAddress(const char * newPrimaryAddress)
{
    this->newPrimaryAddress = newPrimaryAddress;
}

const char * GCSAnnouncementMessage::getReason() const
{
    return this->reason.c_str();
}

void GCSAnnouncementMessage::setReason(const char * reason)
{
    this->reason = reason;
}

omnetpp::simtime_t GCSAnnouncementMessage::getTimestamp() const
{
    return this->timestamp;
}

void GCSAnnouncementMessage::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

int GCSAnnouncementMessage::getDroneCount() const
{
    return this->droneCount;
}

void GCSAnnouncementMessage::setDroneCount(int droneCount)
{
    this->droneCount = droneCount;
}

class GCSAnnouncementMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_newPrimaryAddress,
        FIELD_reason,
        FIELD_timestamp,
        FIELD_droneCount,
    };
  public:
    GCSAnnouncementMessageDescriptor();
    virtual ~GCSAnnouncementMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(GCSAnnouncementMessageDescriptor)

GCSAnnouncementMessageDescriptor::GCSAnnouncementMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(GCSAnnouncementMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

GCSAnnouncementMessageDescriptor::~GCSAnnouncementMessageDescriptor()
{
    delete[] propertyNames;
}

bool GCSAnnouncementMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GCSAnnouncementMessage *>(obj)!=nullptr;
}

const char **GCSAnnouncementMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GCSAnnouncementMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GCSAnnouncementMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int GCSAnnouncementMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_newPrimaryAddress
        FD_ISEDITABLE,    // FIELD_reason
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_droneCount
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *GCSAnnouncementMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "newPrimaryAddress",
        "reason",
        "timestamp",
        "droneCount",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int GCSAnnouncementMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "newPrimaryAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reason") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "droneCount") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *GCSAnnouncementMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_newPrimaryAddress
        "string",    // FIELD_reason
        "omnetpp::simtime_t",    // FIELD_timestamp
        "int",    // FIELD_droneCount
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **GCSAnnouncementMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GCSAnnouncementMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GCSAnnouncementMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GCSAnnouncementMessage *pp = omnetpp::fromAnyPtr<GCSAnnouncementMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GCSAnnouncementMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GCSAnnouncementMessage *pp = omnetpp::fromAnyPtr<GCSAnnouncementMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GCSAnnouncementMessage'", field);
    }
}

const char *GCSAnnouncementMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GCSAnnouncementMessage *pp = omnetpp::fromAnyPtr<GCSAnnouncementMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GCSAnnouncementMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GCSAnnouncementMessage *pp = omnetpp::fromAnyPtr<GCSAnnouncementMessage>(object); (void)pp;
    switch (field) {
        case FIELD_newPrimaryAddress: return oppstring2string(pp->getNewPrimaryAddress());
        case FIELD_reason: return oppstring2string(pp->getReason());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        case FIELD_droneCount: return long2string(pp->getDroneCount());
        default: return "";
    }
}

void GCSAnnouncementMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GCSAnnouncementMessage *pp = omnetpp::fromAnyPtr<GCSAnnouncementMessage>(object); (void)pp;
    switch (field) {
        case FIELD_newPrimaryAddress: pp->setNewPrimaryAddress((value)); break;
        case FIELD_reason: pp->setReason((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        case FIELD_droneCount: pp->setDroneCount(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GCSAnnouncementMessage'", field);
    }
}

omnetpp::cValue GCSAnnouncementMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GCSAnnouncementMessage *pp = omnetpp::fromAnyPtr<GCSAnnouncementMessage>(object); (void)pp;
    switch (field) {
        case FIELD_newPrimaryAddress: return pp->getNewPrimaryAddress();
        case FIELD_reason: return pp->getReason();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        case FIELD_droneCount: return pp->getDroneCount();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GCSAnnouncementMessage' as cValue -- field index out of range?", field);
    }
}

void GCSAnnouncementMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GCSAnnouncementMessage *pp = omnetpp::fromAnyPtr<GCSAnnouncementMessage>(object); (void)pp;
    switch (field) {
        case FIELD_newPrimaryAddress: pp->setNewPrimaryAddress(value.stringValue()); break;
        case FIELD_reason: pp->setReason(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_droneCount: pp->setDroneCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GCSAnnouncementMessage'", field);
    }
}

const char *GCSAnnouncementMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr GCSAnnouncementMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GCSAnnouncementMessage *pp = omnetpp::fromAnyPtr<GCSAnnouncementMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GCSAnnouncementMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GCSAnnouncementMessage *pp = omnetpp::fromAnyPtr<GCSAnnouncementMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GCSAnnouncementMessage'", field);
    }
}

Register_Class(GCSSwitchAckMessage)

GCSSwitchAckMessage::GCSSwitchAckMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

GCSSwitchAckMessage::GCSSwitchAckMessage(const GCSSwitchAckMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

GCSSwitchAckMessage::~GCSSwitchAckMessage()
{
}

GCSSwitchAckMessage& GCSSwitchAckMessage::operator=(const GCSSwitchAckMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void GCSSwitchAckMessage::copy(const GCSSwitchAckMessage& other)
{
    this->droneId = other.droneId;
    this->newGCS = other.newGCS;
    this->switchTime = other.switchTime;
    this->successful = other.successful;
}

void GCSSwitchAckMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->droneId);
    doParsimPacking(b,this->newGCS);
    doParsimPacking(b,this->switchTime);
    doParsimPacking(b,this->successful);
}

void GCSSwitchAckMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->droneId);
    doParsimUnpacking(b,this->newGCS);
    doParsimUnpacking(b,this->switchTime);
    doParsimUnpacking(b,this->successful);
}

int GCSSwitchAckMessage::getDroneId() const
{
    return this->droneId;
}

void GCSSwitchAckMessage::setDroneId(int droneId)
{
    this->droneId = droneId;
}

const char * GCSSwitchAckMessage::getNewGCS() const
{
    return this->newGCS.c_str();
}

void GCSSwitchAckMessage::setNewGCS(const char * newGCS)
{
    this->newGCS = newGCS;
}

omnetpp::simtime_t GCSSwitchAckMessage::getSwitchTime() const
{
    return this->switchTime;
}

void GCSSwitchAckMessage::setSwitchTime(omnetpp::simtime_t switchTime)
{
    this->switchTime = switchTime;
}

bool GCSSwitchAckMessage::getSuccessful() const
{
    return this->successful;
}

void GCSSwitchAckMessage::setSuccessful(bool successful)
{
    this->successful = successful;
}

class GCSSwitchAckMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_droneId,
        FIELD_newGCS,
        FIELD_switchTime,
        FIELD_successful,
    };
  public:
    GCSSwitchAckMessageDescriptor();
    virtual ~GCSSwitchAckMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(GCSSwitchAckMessageDescriptor)

GCSSwitchAckMessageDescriptor::GCSSwitchAckMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(GCSSwitchAckMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

GCSSwitchAckMessageDescriptor::~GCSSwitchAckMessageDescriptor()
{
    delete[] propertyNames;
}

bool GCSSwitchAckMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GCSSwitchAckMessage *>(obj)!=nullptr;
}

const char **GCSSwitchAckMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GCSSwitchAckMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GCSSwitchAckMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int GCSSwitchAckMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_droneId
        FD_ISEDITABLE,    // FIELD_newGCS
        FD_ISEDITABLE,    // FIELD_switchTime
        FD_ISEDITABLE,    // FIELD_successful
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *GCSSwitchAckMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "droneId",
        "newGCS",
        "switchTime",
        "successful",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int GCSSwitchAckMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "droneId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "newGCS") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "switchTime") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "successful") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *GCSSwitchAckMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_droneId
        "string",    // FIELD_newGCS
        "omnetpp::simtime_t",    // FIELD_switchTime
        "bool",    // FIELD_successful
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **GCSSwitchAckMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GCSSwitchAckMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GCSSwitchAckMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GCSSwitchAckMessage *pp = omnetpp::fromAnyPtr<GCSSwitchAckMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GCSSwitchAckMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GCSSwitchAckMessage *pp = omnetpp::fromAnyPtr<GCSSwitchAckMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GCSSwitchAckMessage'", field);
    }
}

const char *GCSSwitchAckMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GCSSwitchAckMessage *pp = omnetpp::fromAnyPtr<GCSSwitchAckMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GCSSwitchAckMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GCSSwitchAckMessage *pp = omnetpp::fromAnyPtr<GCSSwitchAckMessage>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: return long2string(pp->getDroneId());
        case FIELD_newGCS: return oppstring2string(pp->getNewGCS());
        case FIELD_switchTime: return simtime2string(pp->getSwitchTime());
        case FIELD_successful: return bool2string(pp->getSuccessful());
        default: return "";
    }
}

void GCSSwitchAckMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GCSSwitchAckMessage *pp = omnetpp::fromAnyPtr<GCSSwitchAckMessage>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: pp->setDroneId(string2long(value)); break;
        case FIELD_newGCS: pp->setNewGCS((value)); break;
        case FIELD_switchTime: pp->setSwitchTime(string2simtime(value)); break;
        case FIELD_successful: pp->setSuccessful(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GCSSwitchAckMessage'", field);
    }
}

omnetpp::cValue GCSSwitchAckMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GCSSwitchAckMessage *pp = omnetpp::fromAnyPtr<GCSSwitchAckMessage>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: return pp->getDroneId();
        case FIELD_newGCS: return pp->getNewGCS();
        case FIELD_switchTime: return pp->getSwitchTime().dbl();
        case FIELD_successful: return pp->getSuccessful();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GCSSwitchAckMessage' as cValue -- field index out of range?", field);
    }
}

void GCSSwitchAckMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GCSSwitchAckMessage *pp = omnetpp::fromAnyPtr<GCSSwitchAckMessage>(object); (void)pp;
    switch (field) {
        case FIELD_droneId: pp->setDroneId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_newGCS: pp->setNewGCS(value.stringValue()); break;
        case FIELD_switchTime: pp->setSwitchTime(value.doubleValue()); break;
        case FIELD_successful: pp->setSuccessful(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GCSSwitchAckMessage'", field);
    }
}

const char *GCSSwitchAckMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr GCSSwitchAckMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GCSSwitchAckMessage *pp = omnetpp::fromAnyPtr<GCSSwitchAckMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GCSSwitchAckMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GCSSwitchAckMessage *pp = omnetpp::fromAnyPtr<GCSSwitchAckMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GCSSwitchAckMessage'", field);
    }
}

Register_Class(FailoverCompleteMessage)

FailoverCompleteMessage::FailoverCompleteMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

FailoverCompleteMessage::FailoverCompleteMessage(const FailoverCompleteMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

FailoverCompleteMessage::~FailoverCompleteMessage()
{
}

FailoverCompleteMessage& FailoverCompleteMessage::operator=(const FailoverCompleteMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void FailoverCompleteMessage::copy(const FailoverCompleteMessage& other)
{
    this->dronesReconnected = other.dronesReconnected;
    this->failoverStartTime = other.failoverStartTime;
    this->failoverEndTime = other.failoverEndTime;
    this->failoverDuration = other.failoverDuration;
}

void FailoverCompleteMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->dronesReconnected);
    doParsimPacking(b,this->failoverStartTime);
    doParsimPacking(b,this->failoverEndTime);
    doParsimPacking(b,this->failoverDuration);
}

void FailoverCompleteMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->dronesReconnected);
    doParsimUnpacking(b,this->failoverStartTime);
    doParsimUnpacking(b,this->failoverEndTime);
    doParsimUnpacking(b,this->failoverDuration);
}

int FailoverCompleteMessage::getDronesReconnected() const
{
    return this->dronesReconnected;
}

void FailoverCompleteMessage::setDronesReconnected(int dronesReconnected)
{
    this->dronesReconnected = dronesReconnected;
}

omnetpp::simtime_t FailoverCompleteMessage::getFailoverStartTime() const
{
    return this->failoverStartTime;
}

void FailoverCompleteMessage::setFailoverStartTime(omnetpp::simtime_t failoverStartTime)
{
    this->failoverStartTime = failoverStartTime;
}

omnetpp::simtime_t FailoverCompleteMessage::getFailoverEndTime() const
{
    return this->failoverEndTime;
}

void FailoverCompleteMessage::setFailoverEndTime(omnetpp::simtime_t failoverEndTime)
{
    this->failoverEndTime = failoverEndTime;
}

double FailoverCompleteMessage::getFailoverDuration() const
{
    return this->failoverDuration;
}

void FailoverCompleteMessage::setFailoverDuration(double failoverDuration)
{
    this->failoverDuration = failoverDuration;
}

class FailoverCompleteMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_dronesReconnected,
        FIELD_failoverStartTime,
        FIELD_failoverEndTime,
        FIELD_failoverDuration,
    };
  public:
    FailoverCompleteMessageDescriptor();
    virtual ~FailoverCompleteMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(FailoverCompleteMessageDescriptor)

FailoverCompleteMessageDescriptor::FailoverCompleteMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(FailoverCompleteMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

FailoverCompleteMessageDescriptor::~FailoverCompleteMessageDescriptor()
{
    delete[] propertyNames;
}

bool FailoverCompleteMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FailoverCompleteMessage *>(obj)!=nullptr;
}

const char **FailoverCompleteMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FailoverCompleteMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FailoverCompleteMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int FailoverCompleteMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_dronesReconnected
        FD_ISEDITABLE,    // FIELD_failoverStartTime
        FD_ISEDITABLE,    // FIELD_failoverEndTime
        FD_ISEDITABLE,    // FIELD_failoverDuration
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *FailoverCompleteMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dronesReconnected",
        "failoverStartTime",
        "failoverEndTime",
        "failoverDuration",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int FailoverCompleteMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "dronesReconnected") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "failoverStartTime") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "failoverEndTime") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "failoverDuration") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *FailoverCompleteMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_dronesReconnected
        "omnetpp::simtime_t",    // FIELD_failoverStartTime
        "omnetpp::simtime_t",    // FIELD_failoverEndTime
        "double",    // FIELD_failoverDuration
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **FailoverCompleteMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FailoverCompleteMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FailoverCompleteMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FailoverCompleteMessage *pp = omnetpp::fromAnyPtr<FailoverCompleteMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void FailoverCompleteMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FailoverCompleteMessage *pp = omnetpp::fromAnyPtr<FailoverCompleteMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FailoverCompleteMessage'", field);
    }
}

const char *FailoverCompleteMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FailoverCompleteMessage *pp = omnetpp::fromAnyPtr<FailoverCompleteMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FailoverCompleteMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FailoverCompleteMessage *pp = omnetpp::fromAnyPtr<FailoverCompleteMessage>(object); (void)pp;
    switch (field) {
        case FIELD_dronesReconnected: return long2string(pp->getDronesReconnected());
        case FIELD_failoverStartTime: return simtime2string(pp->getFailoverStartTime());
        case FIELD_failoverEndTime: return simtime2string(pp->getFailoverEndTime());
        case FIELD_failoverDuration: return double2string(pp->getFailoverDuration());
        default: return "";
    }
}

void FailoverCompleteMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FailoverCompleteMessage *pp = omnetpp::fromAnyPtr<FailoverCompleteMessage>(object); (void)pp;
    switch (field) {
        case FIELD_dronesReconnected: pp->setDronesReconnected(string2long(value)); break;
        case FIELD_failoverStartTime: pp->setFailoverStartTime(string2simtime(value)); break;
        case FIELD_failoverEndTime: pp->setFailoverEndTime(string2simtime(value)); break;
        case FIELD_failoverDuration: pp->setFailoverDuration(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FailoverCompleteMessage'", field);
    }
}

omnetpp::cValue FailoverCompleteMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FailoverCompleteMessage *pp = omnetpp::fromAnyPtr<FailoverCompleteMessage>(object); (void)pp;
    switch (field) {
        case FIELD_dronesReconnected: return pp->getDronesReconnected();
        case FIELD_failoverStartTime: return pp->getFailoverStartTime().dbl();
        case FIELD_failoverEndTime: return pp->getFailoverEndTime().dbl();
        case FIELD_failoverDuration: return pp->getFailoverDuration();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FailoverCompleteMessage' as cValue -- field index out of range?", field);
    }
}

void FailoverCompleteMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FailoverCompleteMessage *pp = omnetpp::fromAnyPtr<FailoverCompleteMessage>(object); (void)pp;
    switch (field) {
        case FIELD_dronesReconnected: pp->setDronesReconnected(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_failoverStartTime: pp->setFailoverStartTime(value.doubleValue()); break;
        case FIELD_failoverEndTime: pp->setFailoverEndTime(value.doubleValue()); break;
        case FIELD_failoverDuration: pp->setFailoverDuration(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FailoverCompleteMessage'", field);
    }
}

const char *FailoverCompleteMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr FailoverCompleteMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FailoverCompleteMessage *pp = omnetpp::fromAnyPtr<FailoverCompleteMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FailoverCompleteMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FailoverCompleteMessage *pp = omnetpp::fromAnyPtr<FailoverCompleteMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FailoverCompleteMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

