#pragma once

#include "Object.h"
#include "ObjectScene.h"
#include "DrawScene.h"
#include "Controller.h"
#include "AI.h"

pthread_t AddThread(ObjectScene *scene)
{
    pthread_t thread;                                            // Индефикатор потока (указатель на поток)
    pthread_attr_t attr;                                         // Парамметры потока
    pthread_attr_init(&attr);                                    // получаем дефолтные значения атрибутов 
    //pthread_create(&thread, &attr, , (void*)scene);        // Создаем поток

}

void* treadAISynchronize(void* scene)
{
    //ai_scene.synchronize(dynamic_cast<ObjectScene*>(scene));
}