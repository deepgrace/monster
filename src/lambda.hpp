constexpr auto lambda()
{
    return

    [=]<typename... Args>()
    { 
        return [&]<auto... N>(auto... args)
        { 
            return sizeof ...(Args) + sizeof ...(N) + sizeof ...(args);
        }.template operator()<'+'>(0);

    }.template operator()<int>();
}
