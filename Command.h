#pragma once

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

class WaterCommand : public Command {
public:
    void execute() override;
};
class FertilizeCommand : public Command {
public:
    void execute() override;

};

class HarvestCommand : public Command {
public:
    void execute() override;
};

class PatrolCommand : public Command {
public:
    void execute() override;
};

class ServeCommand : public Command {
public:
    void execute() override;
};