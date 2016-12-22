#include "data.h"

Data::Data()
{
	this->context = new VulkanContext();
}

Data::~Data()
{
}
std::unique_ptr<Data> Data::m_instance;
std::once_flag Data::m_onceFlag;
Data& Data::getInstance()
{
	std::call_once(m_onceFlag,
		[] {
		m_instance.reset(new Data);
	});
	return *m_instance.get();
}

VulkanContext * Data::getContext()
{
	return context;
}

