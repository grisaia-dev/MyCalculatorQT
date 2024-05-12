#!/bin/zsh

if [ "$#" -lt 1 ];
then
    echo -e "\033[31mНет нужных аргументов! Пример использования:\033[0m"
    echo "-- $0 -g[Генерация файлов cmake] -b[Сборка проекта]"
    exit 1
fi

if [ "$2" = "-g" ];
then
    echo -e "$1: \033[31mМожет быть только 2-ым аргументом!\033[0m"
    exit 1
fi

while [ -n "$1" ]
do
    case "$1" in
    -g)
        echo -e "-- \033[32mГенерация проекта..\033[0m"
        cmake -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=1
        echo -e "-- \033[32mГенерация завершена!\033[0m"
    ;;
    -b)
        echo -e "-- \033[32mСборка проекта..\033[0m"
        cd build/ && make && cd ..
        echo -e "-- \033[32mСборка завершена!\033[0m"
    ;;
    -o)
        echo -e "-- \033[32mЗапуск программы..\033[0m\n"

        case "$OSTYPE" in
            darwin*)
                #cd bin && open MyCalculator.app
                cd bin/MyCalculator.app/Contents/MacOS && ./MyCalculator
                cd ..
            ;;
            linux*)
                cd bin && ./MyCalculator
                cd ..
            ;;
            *)
                echo "unknown: $OSTYPE"
            ;;
        esac
        echo -e "-- \033[32mРабота программы завершена!\033[0m"
    ;;
    *)
        echo -e "$1: \033[31mНет такого аргумента!\033[0m"
        echo "Пример использования:"
        echo "-- $0 -g[Генерация файлов cmake] -b[Сборка проекта]"
        break
    ;;
    esac
    shift
done
