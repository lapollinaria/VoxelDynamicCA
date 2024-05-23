# VoxelDynamicCA
 Метод генерации динамических ландшафтов на примере океанического дна и тектонической активности.
 Используется подход клеточных автоматов и воксели.
 Изменения рельефа происходят в рантайме, возможна генерация возвышенностей и разломов.

Инструкции по запуску:
1. Для запуска проекта понадобится Unreal Engine версии 5.2. Получить нужную версию можно из Epic Games Launcher, если он не установлен, то:
- Загрузить launcher по ссылке https://www.unrealengine.com/en-US/download
- Установить launcher
- Зарегистрироваться или войти в аккаунт Epic Games

В Epic Games launcher выбрать вкладку Unreal Engine -> Library -> Engine Versions и установить версию 5.2

2. Для запуска проекта понадобится Visual Studio, инструкции можно найти по ссылке https://learn.microsoft.com/ru-ru/visualstudio/install/install-visual-studio?view=vs-2022
3. После клонирования репозитория, нужно создать решение, нажав на файл .uproject правой кнопкой мыши и выбрав соответствующую опцию
4. После создания файла .sln его нужно открыть с помощью Visual Studio и запустить проект по кнопке Start without debugging (Ctrl + F5)
5. Должен открыться уровень Map, если нет, его надо открыть вручную
6. На данный момент пользоватльское переключение не реализовано, поэтому настройки должны быть Naive Chunk, 2D генерация
7. По кнопке пуск сгенерируется первоначальный рельеф, по кнопке M рельеф можно менять


Примеры работы программы:

Создание разломов:
![2024-05-23 22-51-50 (1)](https://github.com/lapollinaria/VoxelDynamicCA/assets/46728296/92c8bcfc-7728-4354-9b43-bc5127d8cd78)

Создание возвышенностей:
![2024-05-12 20-29-54 (2)](https://github.com/lapollinaria/VoxelDynamicCA/assets/46728296/afaab3c7-fe5f-4e2a-8bb3-4093a0274dac)

