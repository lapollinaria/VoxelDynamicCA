# VoxelDynamicCA
 Проект в Unreal Engine 5, реализующий метод генерации динамических ландшафтов на примере океанического дна и тектонической активности.
 Используется подход клеточных автоматов и воксели.
 Изменения рельефа происходят в рантайме, возможна генерация возвышенностей и разломов.

Разработана схема реализации алгоритма процедурной генерации динамических ландшафтов, который учитывает особенности реальных геологических феноменов и использует метод клеточных автоматов. Именно клеточные автоматы, симулирующие постоянно развивающиеся и саморегулирующиеся системы и обеспечивают искомую динамику для получаемых рельефов. 
Проведены практические эксперименты по имплементации алгоритма в Unreal Engine на основе разработанных ранее правил для клеточных автоматов. В процессе перенесения экспериментов в трёхмерное пространство обнаружены ограничения по работе с картами клеточных автоматов, которые привели к выбору в качестве программной имплементации подход воксельных миров. Созданы тестовые карты разных конфигураций и масштабов, на основе полученных визуальных данных осуществлена доработка правил и ограничений. Проведена оптимизация рассмотренной схемы алгоритма и программной имплементации. С учётом метода отсечения граней, карту возможно сгенерировать меньше, чем за секунду, а динамические изменения происходят без заметных для глаза пауз в движении камеры и игровом окружении. 

Проект является частью магистерской выпускной квалификационной работы по образовательной программе "Технологии разработки компьютерных игр". Работа выполнена на языке C++ в игровом движке Unreal Engine 5.

###### Шилова Полина. Контакт для связи (tg username): vntrix 

#### Обзор метода:
Проблема, которую решает данная работа, заключается в отсутствии алгоритмов, которые могли бы создавать изменения в ландшафте на больших участках карты во время игры. Клеточные автоматы обеспечивают возможность создания логичных изменений с помощью настройки правил. Важно отметить особенности тектонических процессов: человеку заметны результаты быстрых (сейсмических) процессов, под влиянием таких процессов образуются складчатые и разрывные структуры в рельефе, причём изменения локализуются вдоль границ тектонических плит и имеют вытянутую, линейную форму. 

Карта высот, которая меняется в процессе работы игры и на основе которой меняется ландшафт, состоит из слоёв, каждый из которых представляет собой сетку клеточных автоматов. Если клетка находится в выключенном состоянии, то воксель на соответствующей высоте пустой. В зависимости от количества живых соседей клетки включаются и выключаются с разной вероятностью. Во избежание появления летающих горных пород пещеры и прочие нависающи структуры в рельефов отсутствуют.

#### Инструкции по запуску:
1. Для запуска проекта понадобится Unreal Engine версии 5.2. Получить нужную версию можно из Epic Games Launcher, если он не установлен, то:
- Загрузить launcher по ссылке https://www.unrealengine.com/en-US/download
- Установить launcher
- Зарегистрироваться или войти в аккаунт Epic Games

В Epic Games launcher выбрать вкладку Unreal Engine -> Library -> Engine Versions и установить версию 5.2

2. Для запуска проекта понадобится Visual Studio, инструкции можно найти по ссылке https://learn.microsoft.com/ru-ru/visualstudio/install/install-visual-studio?view=vs-2022
3. Сохранить проект (лучше архивом) и сгенерировать решение Visual Studio (ПКМ по файлу uproject)
4. Запустить решение по кнопке Start without debugging (Ctrl + F5)
5. Должен открыться уровень Map, если нет, его надо открыть вручную (file -> open level -> в папке content уровень Map)
6. На данный момент пользоватльское переключение не реализовано, поэтому настройки должны быть Chunk type: Naive Chunk, Generation type: 2D генерация (Это дефолтные настройки, они уже установлены)
7. По кнопке пуск сгенерируется первоначальный рельеф, по кнопке M рельеф можно менять


#### Примеры работы программы:

Создание разломов:

 ![2024-05-23 22-51-50 (1)](https://github.com/lapollinaria/VoxelDynamicCA/assets/46728296/92c8bcfc-7728-4354-9b43-bc5127d8cd78)

Создание возвышенностей:

 ![2024-05-12 20-29-54 (2)](https://github.com/lapollinaria/VoxelDynamicCA/assets/46728296/afaab3c7-fe5f-4e2a-8bb3-4093a0274dac)

##### Ссылка на полный текст работы:
https://drive.google.com/file/d/1KgnOMavxXJlxVBlnqGas1QxDvH5MsX1K/view?usp=drive_link
