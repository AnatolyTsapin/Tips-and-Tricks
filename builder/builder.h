#ifndef BUILDER_BUILDER_H_
#define BUILDER_BUILDER_H_

#include <utility>
#include <string>
#include <vector>

struct Card
{
    std::string name;
    std::string surname;
    std::string jobTitle;
    std::string email;
    std::vector<std::string> phone;
};

class Base
{
public:
    Base() = default;
    explicit Base(Card&& card) :
        card(std::move(card))
    {}

protected:
    Card card;
};

static constexpr bool ready(size_t N, size_t S, size_t J, size_t E, size_t P)
{
    return N == 0 && S == 0 && (E == 0 || P < 3);
}

template<size_t N, size_t S, size_t J, size_t E, size_t P, bool R = ready(N, S, J, E, P)>
class Builder;

template<size_t N, size_t S, size_t J, size_t E, size_t P>
class Name : public virtual Base
{
public:
    using Base::Base;

    auto name(const std::string& value) &&
    {
        card.name = value;
        return Builder<N - 1, S, J, E, P>(std::move(card));
    }
};

template<size_t S, size_t J, size_t E, size_t P>
class Name<0, S, J, E, P> : public virtual Base
{
public:
    using Base::Base;
};

template<size_t N, size_t S, size_t J, size_t E, size_t P>
class Surname : public virtual Base
{
public:
    using Base::Base;

    auto surname(const std::string& value) &&
    {
        card.surname = value;
        return Builder<N, S - 1, J, E, P>(std::move(card));
    }
};

template<size_t N, size_t J, size_t E, size_t P>
class Surname<N, 0, J, E, P> : public virtual Base
{
public:
    using Base::Base;
};

template<size_t N, size_t S, size_t J, size_t E, size_t P>
class JobTitle : public virtual Base
{
public:
    using Base::Base;

    auto jobTitle(const std::string& value) &&
    {
        card.jobTitle = value;
        return Builder<N, S, J - 1, E, P>(std::move(card));
    }
};

template<size_t N, size_t S, size_t E, size_t P>
class JobTitle<N, S, 0, E, P> : public virtual Base
{
public:
    using Base::Base;
};

template<size_t N, size_t S, size_t J, size_t E, size_t P>
class Email : public virtual Base
{
public:
    using Base::Base;

    auto email(const std::string& value) &&
    {
        card.email = value;
        return Builder<N, S, J, E - 1, P>(std::move(card));
    }
};

template<size_t N, size_t S, size_t J, size_t P>
class Email<N, S, J, 0, P> : public virtual Base
{
public:
    using Base::Base;
};

template<size_t N, size_t S, size_t J, size_t E, size_t P>
class Phone : public virtual Base
{
public:
    using Base::Base;

    auto phone(const std::string& value) &&
    {
        card.phone.push_back(value);
        return Builder<N, S, J, E, P - 1>(std::move(card));
    }
};

template<size_t N, size_t S, size_t J, size_t E>
class Phone<N, S, J, E, 0> : public virtual Base
{
public:
    using Base::Base;
};

template<size_t N, size_t S, size_t J, size_t E, size_t P, bool R>
class Builder : public virtual Base,
    public virtual Name<N, S, J, E, P>,
    public virtual Surname<N, S, J, E, P>,
    public virtual JobTitle<N, S, J, E, P>,
    public virtual Email<N, S, J, E, P>,
    public virtual Phone<N, S, J, E, P>
{
public:
    using Base::Base;
};

template<size_t N, size_t S, size_t J, size_t E, size_t P>
class Builder<N, S, J, E, P, true> : public virtual Base,
    public virtual Name<N, S, J, E, P>,
    public virtual Surname<N, S, J, E, P>,
    public virtual JobTitle<N, S, J, E, P>,
    public virtual Email<N, S, J, E, P>,
    public virtual Phone<N, S, J, E, P>
{
public:
    using Base::Base;

    Card build() &&
    {
        return std::move(card);
    }
};

using CardBuilder = Builder<1, 1, 1, 1, 3>;

#endif /* BUILDER_BUILDER_H_ */
