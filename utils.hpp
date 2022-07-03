#ifndef UTILS_HPP
#define UTILS_HPP

#define GET(name, value) const auto &name() const {return value;}
#define GET_NUMBER(name, value) const auto name() const {return value;}
#define GET_CONTAINER_MEMBER(name, value, id) const auto &name(size_t id) const {return value[id];}

#endif
