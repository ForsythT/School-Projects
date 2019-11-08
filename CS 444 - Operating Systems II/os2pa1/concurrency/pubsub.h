#pragma once
#include <unistd.h>
#include "mersenne.h"
#include "queue.h"
#include "event.h"
#include "producer.h"
#include "consumer.h"
#include "randomizationInterface.h"
struct Event ProduceEvent();
void PublishEvent(Event e);
struct Event SubscribeEvent();