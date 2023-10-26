#ifndef BIGINTEGER_H
#define BIGINTEGER_H

struct BigInteger initialize(char* str);
void display(struct BigInteger a);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
struct BigInteger div1(struct BigInteger a, struct BigInteger b);

#endif