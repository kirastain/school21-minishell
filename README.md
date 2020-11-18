# school21-minishell


## Commands

### echo

echo - display a line of text


SYNOPSIS

       echo [SHORT-OPTION]... [STRING]...
       echo LONG-OPTION


-n     do not output the trailing newline


### cd


NAME

cd - Change the shell working directory.


SYNOPSIS

       cd [-L|[-P [-e]] [-@]] [dir]


DESCRIPTION

Change the shell working directory.
    
Change the current directory to DIR.  The default DIR is the value of the
HOME shell variable.
    
The variable CDPATH defines the search path for the directory containing
DIR.  Alternative directory names in CDPATH are separated by a colon (:).
A null directory name is the same as the current directory.  If DIR begins
with a slash (/), then CDPATH is not used.
    
If the directory is not found, and the shell option \`cdable_vars\' is set,
the word is assumed to be  a variable name.  If that variable has a value,
its value is used for DIR.
    
Options:

-L	force symbolic links to be followed: resolve symbolic
    		links in DIR after processing instances of \`..\'
-P	use the physical directory structure without following
    		symbolic links: resolve symbolic links in DIR before
    		processing instances of \`..\'
-e	if the -P option is supplied, and the current working
    		directory cannot be determined successfully, exit with
    		a non-zero status
-@	on systems that support it, present a file with extended
    		attributes as a directory containing the file attributes
    
The default is to follow symbolic links, as if \`-L\' were specified.
\`..\' is processed by removing the immediately previous pathname component
back to a slash or the beginning of DIR.
    
Exit Status:

Returns 0 if the directory is changed, and if $PWD is set successfully when
-P is used; non-zero otherwise.

### pwd

NAME

pwd - print name of current/working directory

SYNOPSIS

       pwd [OPTION]...

DESCRIPTION

Print the full filename of the current working directory.


### export

export - set the export attribute for variables
 
SYNOPSIS

       export name[=word]...

export -p 
 
DESCRIPTION

The shell shall give the export attribute to the variables corresponding to the specified names, which shall cause them to be in the environment of subsequently executed commands. If the name of a variable is followed by = word, then the value of that variable shall be set to word.

The export special built-in shall support the Base Definitions volume of IEEE Std 1003.1-2001, Section 12.2, Utility Syntax Guidelines.

When -p is specified, export shall write to the standard output the names and values of all exported variables, in the following format:

    "export %s=%s\n", <name>, <value>

if name is set, and:


    "export %s\n", <name>

if name is unset.

The shell shall format the output, including the proper use of quoting, so that it is suitable for reinput to the shell as commands that achieve the same exporting results, except:

Read-only variables with values cannot be reset.

Variables that were unset at the time they were output need not be reset to the unset state if a value is assigned to the variable between the time the state was saved and the time at which the saved output is reinput to the shell.

When no arguments are given, the results are unspecified.   

### unset

NAME

unset - unset values and attributes of variables and functions 

SYNOPSIS

       unset [-fv] name ...  

DESCRIPTION

Each variable or function specified by name shall be unset.

Unsetting a variable or function that was not previously set shall not be considered an error and does not cause the shell to abort.

The unset special built-in shall support the Base Definitions volume of IEEE Std 1003.1-2001, Section 12.2, Utility Syntax Guidelines.

Note that:

    VARIABLE=

is not equivalent to an unset of VARIABLE; in the example, VARIABLE is set to "" . Also, the variables that can be unset should not be misinterpreted to include the special parameters (see Special Parameters ).   

### env

NAME

unset - unset values and attributes of variables and functions
 
SYNOPSIS

       unset [-fv] name ...  

DESCRIPTION

Each variable or function specified by name shall be unset.

Unsetting a variable or function that was not previously set shall not be considered an error and does not cause the shell to abort.

The unset special built-in shall support the Base Definitions volume of IEEE Std 1003.1-2001, Section 12.2, Utility Syntax Guidelines.

Note that:

    VARIABLE=

is not equivalent to an unset of VARIABLE; in the example, VARIABLE is set to "" . Also, the variables that can be unset should not be misinterpreted to include the special parameters (see Special Parameters ).   

### exit

sh

exit causes the calling shell or shell script to exit with the exit status specified by n. If n is omitted the exit status is that of the last command executed (an EOF also causes the shell to exit.) 

## Main function and env

       int main( int argc, char *argv[], char *envp[] )

Третья строка приведенного выше примера, где функция main принимает три параметра, представляет собой расширение Майкрософт для стандарта ANSI C. Третий параметр (envp) — это массив указателей на переменные среды. Массив envp завершается пустым указателем. 

## Parser


Как сделать парсер для minishell.


1) Лексический анализ.
 Мы получили строку с вводом пользователя. Она состоит из отдельных слов и спецальных символов. В лексическом анализе мы обработаем спецальные символы и разобьем строку на токены, которые далее пойдут в логический анализ. Но есть пару вещей, которые мы должны сделать до этого.


 1. Обработать некорректные последовательности следующих символов";<>|". Несколько примеров: 
 - | без предшествующего токена - если он в начале строки - то это ошибка.
 - ";;" - ошибка, в любом месте.
 - ';' в начале строки или после - Одни кавычки - это норм. Не делать ничего
 - Комбинации ";|", "|;" - ошибка
 - '<' или '>' или '>>' в конец строки
 - "<|" (обратите внимание, что ">|" является валидным случаем, и раценивается как '>')
 - "||" и "&&"(если без бонусов), или "|||" и "&&&"(если с бонусами)
 И другие, которые вы найдете сами, когда будете тестировать шелл.


 2. Если строка заканчивается на '|', то мы должны попросить пользователя дописать команду. Если она снова закончится на '|', то мы должны снова попоросить дописать команду. И так в цикле.


 Далее начинается именно сам лексический анализ, в процессе которого мы создаем токены. Мы не знаем, сколько у нас будет токенов, поэтому мы используем односвязный список для их хранения, но затем его можно перевести в двумерный массив.
 Мы идем по строке и пропускаем все пробелы. Как только натыкаемся на символ, отличный от пробела, проверяем, есть ли он среди спецальных символов. Если нет, записываем в токен (просто нужна функция, которая перезаписывает массив с добавлением одного символа, после cub3d такая у некоторых появилась). Для обработки каждого специального символа у нас должны быть своя функция.
 - Если мы видим '\' то мы тупо добавляем следующий символ в токен, каким бы он ни был.
 - Если это $, то мы должны посмотреть в массив переменных окружения, найти там соответствующую переменную, и вставить ее значение.
 - Если это '<', '>', ">>", '|' то если до этого в нашем токене уже были символы, мы заканчиваем его запись и посылаем в список. Сам спец символ мы кладем в отдельный токен и тоже посылаем в список. И идем дальше.
 - Пробел говорит о том, что токен закончился и мы кладем его в список.
 - Кавычки. В них мы передаем двойной указатель на строку, по которой идем. Если у нас одинарные кавчки, то мы просто кладем все что в них было в токен. В двойных кавчках работают '$', '\', ''' но с отличиями от своего стандартного поведения.
 - ';' говорит о завершении команды. Мы отдаем список с токенами в логический анализ.


2) Логический анализ.
 Продукт логического анализа - массив структур, в каждой из которых будет вся информация о выполняемой команде. Между каждой командой стоит пайп. Т.е., мы будем выполнять команду за командой, и передавать стандартный вывод как стандартный ввод в следующую команду. Кароче, мы тупа разбиваем массив токенов по токену '|'. Я написал функцию сплит для двумерного массива, которая ищет определенную строку, и по ней разбивает весь двумерный массив на трехмерный массив двумерных массивов. Но вы это можете сделать как-нибудь проще. Поля структуры:
 - Имя запускаемой команды.
 - Массив аргументов (сначала будет список, потом переведем в массив)
 - Файловый дискриптор входного перенаправления.
 - Файловый дискриптор выходного перенаправления.
 - Другие служебные поля, например самописанная ли это функция (echo, pwd, cd, export, unset), пид будущего процесса, число аргументов.
 Значит, логика такая. Идем по токенам, если видим токены '<', '>', '>>' то это говорит нам о том, что следующий токен будет именем файла для перенаправления. Если у нас был токен '<', то мы проверяем, есть ли такой файл. Если есть, открываем его файловый дискриптор. Если '>' или '>>' то мы создаем файл с таким именем, и сохраняем его файловый дискриптор. Если мы видим несколько перенаправлений в одну сторону, то каждый раз мы закрываем предыдущий файловый дискриптор и открываем новый.
 Далее. Если мы видим '|', то это говорит о том, что команда закончилась, идем к следующей.
 Далее. Если мы видим любой другой токен (а любой другой токен не будет являться специальным) то мы проверяем, встречалось ли нам имя программы, которую мы запустим. Т.е. у нас должна быть переменная с именем программы, которая изначально NULL. И если она NULL, то имя программы нам не встречалось, и значит, текущий токен - запускаемая нами программа. И что же делать? Для начала, нужно определить, входит ли она в список функций, которые мы должны реальизовать сами (echo, cd, export ...). Если да, то просто кладем ее как есть в структуру и где-нибудь помечаем, что запускаемая программа является самописной функцией. Если не является, то мы проверяем, есть ли программа с таким именем по пути. Т.е. смотрим, начинается ли токен с точки (или слеша). Нужно прочекать, не директория ли это, с помощью opendir. Затем пытаемся открыть файл с помощью open (ошибку, связанную с тем, что файл является не исполняемым, придется обрабатывать не в парсере, а аж после execve - она вернет ошибку). Если файл открывается - мы кладем токен в структуру. И последний вариант, самый неприятный - программа, которая лежит в одной из папок по переменной $PATH. Все команды, которые мы привыкли запускать в терминале, на самом деле просто программы, путь к которым указан в этой переменной. Когда мы вводим ls, шелл подставляет к названию программы поочереди каждый путь, и пытается запустить. Если например сделать unset PATH, то команды перестанут работать, и для их выполнения придется прописывать абсолютный путь. Так вот, если предыдущие варианты не прокатили, то нам придеться взять каждый путь из переменной PATH, подставить его к имени нашей программы, и чекнуть с помощью так же, как в случае с путем.
 Как только мы у нас появилось имя программы, все дальнейшие не специальные токены мы просто кладем как аргументы. Сначала в список, потом переводим в массив. Когда встречаем '|' считаем структуру команды заполненой, и идем к следующей. Когда дойдем до конца, отправляем этот массив структур на выполнение.
