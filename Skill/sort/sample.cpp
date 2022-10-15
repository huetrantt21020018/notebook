sort(mMyClassVector.begin(), mMyClassVector.end(),
    [](const MyClass & a, const MyClass & b)
{
    return a.mProperty > b.mProperty;
});