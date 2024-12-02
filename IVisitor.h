#pragma once

class IVisitor {
public:
    virtual ~IVisitor() = default;
    virtual void Visit(struct DoubleAttackArguments& args) = 0;
    virtual void Visit(struct ScanerArguments& args) = 0;
    virtual void Visit(struct ShellingArguments& args) = 0;
};