#include "entity.h"

namespace SUData {
Entity_C::Entity_C(const SUCore::EntityDataBank_C &dataBank, QObject *parent) : QObject(parent),
  m_dataBank(dataBank)
{

}
}
