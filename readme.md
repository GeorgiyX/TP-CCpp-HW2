## Что это
Это репозиторий ДЗ#2 по курсу "Углублённое программирование на C/С++".

[![Build Status](https://travis-ci.com/GeorgiyX/TP-CCpp-HW2.svg?branch=dev-homework)](https://travis-ci.com/GeorgiyX/TP-CCpp-HW2)  [![codecov](https://codecov.io/gh/GeorgiyX/TP-CCpp-HW2/branch/dev-homework/graph/badge.svg)](https://codecov.io/gh/GeorgiyX/TP-CCpp-HW2)

### Условия задания (Вариант #21)

Сравните и выведите в консоль время работы последовательного и параллельного с (использованием нескольких процессов) алгоритмов, каждый из которых выделяет в динамической памяти числовой массив размером 100 Мб и подсчитывает элементарную контрольную сумму массива. Способ подсчета контрольной суммы — сумма всех чисел по модулю 1024.

## Требования к реализации
* Грамотное разбиение проекта на файлы.
* Наличие двух реализаций – последовательной и параллельной, оформленных в виде статической и динамической библиотек соответственно, а также тестирующей программы (скрипт bash, запускаем две проги, сравниваем), которая будет сравнивать на разных входных данных результаты обеих реализаций между собой;
* Максимальная утилизация ресурсов процессора при параллельной обработке данных путём использования нескольких процессов или потоков;
* Продуманные структуры данных в целях экономии оперативной памяти;
* Реализация алгоритмов, эффективно взаимодействующих с кэш-памятью.
* Развернуть CI, в рамках которого автоматизировать сборку проекта, прохождение юнит-тестов под valgrind, генерацию отчёта о покрытии кода тестами, линтера и статического анализатора исходного кода;
* Компиляция должна происходить с флагами `-Wall -Werror -Wpedantic`, то есть необработанных ворнингов быть не должно;
* количество потоков/процессов должно быть не захардкожено, а определяться в зависимости от возможностей системы (например, в зависимости от количества ядер процессора);
* при разработке обеих библиотек стоит делать общий интерфейс, не раскрывая особенностей реализации;
* библиотеки должны быть взаимозаменяемыми - конкретная реализация (последовательная/параллельная) - использоваться в зависимости от конфигурации сборки;
* юнит-тесты должны быть реализованы для обеих реализаций (последовательной/параллельной). Покрытие тестами должно быть максимально возможным;
* должны присутствовать стресс-тесты. Они могут быть реализованы внешним образом, запуская две разные программы - одну со статической библиотекой с последовательной реализацией, вторую - с динамической библиотекой с параллельной реализацией, и сравнивая их выводы друг с другом.
* если в задании сказано, что программа должна обрабатывать файлы объёмом 100 Мб – это лишь ориентир, на которых программа точно должна работать, и на котором имеет смысл делать замеры производительности и эффективности алгоритмов. Поэтому тесты на такой объём должны быть. Однако сама программа должна уметь работать с произвольными размерами входных данных
* измерение времени должно осуществляться внешним образом, а не внутри кода библиотек. При этом необходимо делать несколько замеров и усреднять. Стоит помнить о том, что clock() в многопоточных приложениях работает не так, как ожидается.