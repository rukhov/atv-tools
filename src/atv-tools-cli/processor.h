#pragma once

template <typename InT, typename OutT = std::remove_cv_t<InT>>
class processor
{
public:
    using in_span_t = std::span<const InT>;
    using out_span_t = std::span<std::remove_cv_t<OutT>>;
    using span = in_span_t;

    virtual ~processor() = default;
    virtual out_span_t process(in_span_t const &) = 0;
    virtual OutT process(InT s) { return 0; };
};
