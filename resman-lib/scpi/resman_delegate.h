#ifndef DELEGATE_H
#define DELEGATE_H

#include <scpiobject.h>
#include <memory>

namespace SCPI
{
/**
  @brief This will represent commands in the SCPI tree

  But it will not implement any logic
  */
class Delegate : public ScpiObject
{
public:
    Delegate();
    Delegate(const QString& t_name, quint8 t_type);
    bool executeSCPI(const QString &t_input, QString &t_output) override;
};

typedef std::shared_ptr<Delegate> DelegatePtr;

}
#endif // DELEGATE_H
