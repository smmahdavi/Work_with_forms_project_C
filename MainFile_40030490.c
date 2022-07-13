#define _CRT_SECURE_NO_WARNING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Macros =============================================================================================================================================================================================

#define MaxLen 300
#define MaxLen2 20000 // it's Greater :)

#define put_character(character, num_of_chars) \
    for (int i = 0; i < num_of_chars; i++)     \
        putchar(character);

#define enter_to_continue()                      \
    printf("\n Enter number 1 to continue... "); \
    while (getchar() != '1')
;

// Structs ============================================================================================================================================================================================

struct components_details
{
    int x;
    int y;
    int type;
    int width;
    int height;
    int num_of_CheckBox_options;
    char name_of_lable[MaxLen2];
    char name_of_button[MaxLen2];
    char label_of_TextBox[MaxLen2];
} component;

struct index_of_components_details
{
    int index1; // index of details;
    int index2; // index of names arr (arr_of_componetns_names);
} index;

struct form_details
{
    char password[MaxLen];
    char all_in_form[MaxLen][MaxLen]; // every chars in form;
    char all_saved_passwords[MaxLen2];
    int num_all_saved_passwords;
} Form;

struct run_part_flags
{
    int run_with_part1_create;
    int run_with_part1_load;
    int run_with_part1;
    int run_with_part2;
} run_flag;

struct some_good_flags // :)
{
    int are_inputs_entered;        // This is used after entering details of the first component (used in part one);
    int stay_in_password_checking; // During checking validation of password;
    int show_command_options;
    int first_command_descriptions_part2;
} flag;

struct running_form_mods
{
    int Add;
    int Find;
    int Edit;
    int Remove;
    int Update;
} runnin_mod;

// Functions =========================================================================================================================================================================================

// Attention: Dear programmer, this project writed in two parts (in proper functions); Part 1 is included phaze 1 and 2 and Part two is included phaze 3;

// Common functions ___________________________________________________________________________________________________________________________________________________________________________

// put functions ..............................................................................................................................................

void put_words_in_FormArr(int x, int y, int length_of_word, char Word[])
{
    int index_of_word = 0;
    for (int i = x; i < x + length_of_word; i++)
        Form.all_in_form[y][i] = Word[index_of_word++];
}

void put_chars_in_FormArr(int mod, int x, int y, int length, char character)
{
    if (mod) // mod == 1 is for putting in rows (in per row of form) (Horizontal)
    {
        for (int i = (x + 1); i < (x + 1 + length); i++)
            Form.all_in_form[y][i] = character;
    }
    else // mod == 0 is for columns :) (Vertical)
    {
        for (int i = (y + 1); i < (y + 1 + length); i++)
            Form.all_in_form[i][x] = character;
    }
}

void put_chars_with_a_word(int mod, int called_in_PutButton, int total_length, char character, char word[]) // word: it can be a word or a sentence :)
{
    int len_of_word = strlen(word);
    int len_of_part_one = ((total_length - len_of_word - 2) / 2);             // Before word;
    int len_of_part_tow = (total_length - len_of_part_one - len_of_word - 2); // After word;

    if (mod) // put chars with a word in form array (in all_in_form arr);
    {
        int Y = 0;
        int X = (component.x * 3);

        if (called_in_PutButton)
        {
            Y = (component.y + ((component.width / 2) + 1)); // Check put_button function;
            X -= 1;
        }
        else
            Y = (component.y + 1); // Why +1? reson in put_TextBox function :);

        put_chars_in_FormArr(1, X, Y, len_of_part_one, character);
        put_words_in_FormArr((X + len_of_part_one + 2), Y, len_of_word, word);
        put_chars_in_FormArr(1, (X + len_of_part_one + len_of_word + 2), Y, len_of_part_tow, character);
    }
    else // put chars with a word in termial (same print);
    {
        put_character(character, len_of_part_one);
        printf(" %s ", word);
        put_character(character, len_of_part_tow);
    }
}

// Finding functions ..........................................................................................................................................

int find_number(char arr[])
{
    int len_of_arr = strlen(arr);
    for (int i = 0; i < len_of_arr; i++)
    {
        if (arr[i] >= '0' && arr[i] <= '9')
            return 1;
    }
    return 0;
}

int find_letter(char arr[])
{
    int len_of_arr = strlen(arr);
    for (int i = 0; i < len_of_arr; i++)
    {
        if ((arr[i] >= 'A' && arr[i] <= 'Z') || (arr[i] >= 'a' && arr[i] <= 'z'))
            return 1;
    }
    return 0;
}

int find_char(char arr[])
{
    int len_of_arr = strlen(arr);
    for (int i = 0; i < len_of_arr; i++)
    {
        if (!((arr[i] >= 'A' && arr[i] <= 'Z') || (arr[i] >= 'a' && arr[i] <= 'z')) && !(arr[i] >= '0' && arr[i] <= '9') && arr[i] != EOF)
            return 1;
    }
    return 0;
}

int find_invalid_chars(char arr[]) // Invalid chars: characters that are not allowed to making a file name;
{
    int len_of_arr = strlen(arr);
    for (int i = 0; i < len_of_arr; i++)
    {
        if (arr[i] == '\\' || arr[i] == '/' || arr[i] == '*' || arr[i] == '<' || arr[i] == '>' || arr[i] == '\"' || arr[i] == '?' || arr[i] == ':' || arr[i] == '|') // Invalid characters for making a file name;
            return 1;
    }
    return 0;
}

// Proper functions ___________________________________________________________________________________________________________________________________________________________________________

// Part One --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Validation fubctions ......................................................................................................................................

int is_password_exist(int length_of_pass, char pass[])
{
    int index_of_pass = 0;
    int num_of_founded_chars_in_pass = 0;
    char passwords[MaxLen2];

    FILE *PF = fopen("passwords.txt", "r");
    fscanf(PF, "%s", passwords);
    fclose(PF);

    for (int i = 0; passwords[i] != '\0'; i++)
    {
        if (passwords[i] == pass[index_of_pass++])
        {
            num_of_founded_chars_in_pass++;
            if (num_of_founded_chars_in_pass == length_of_pass)
                return 1;
        }
        else
        {
            index_of_pass = 0;
            num_of_founded_chars_in_pass = 0;
        }
    }

    return 0;
}

void is_password_valid()
{
    int is_number_founded = 0;
    int is_letter_founded = 0;
    int is_character_founded = 0;
    int len_of_pass = strlen(Form.password);

    flag.stay_in_password_checking = 1;
    if (len_of_pass > 16)
    {
        printf("\n Your password is too long (it should be less than 16 (16 or less) charaacters); Enter another...");
        make_new_component();
    }
    else if (len_of_pass < 4)
    {
        printf("\n Your password is too short (it should be more than 4 (4 or more) charaacters); Enter another...");
        make_new_component();
    }
    else if (is_password_exist(len_of_pass, Form.password))
    {
        printf("\n This password is already used; Enter another...");
        make_new_component();
    }
    else if (!(find_number(Form.password) && find_letter(Form.password) && find_char(Form.password)) || find_invalid_chars(Form.password))
    {
        printf("\n Your password is incorrect (it should be consist numbers, letters and valid characters); Enter another...");
        make_new_component();
    }
    else
        flag.stay_in_password_checking = 0;
}

void is_name_valid(char name_arr[]) // For lable of TextBox and name of button;
{
    int max_lenght = (3 * component.height - 2); // Maximum allowed length for choosed name; why -2? becuse choosed name has two white spaces (in left and right side);
    while (strlen(name_arr) > max_lenght)
    {
        printf("\n This name is too long; Maximum length that you can consider for your name is %d characters;", max_lenght);
        printf("\n Please write a valid name: ");
        if (component.type == 1)
            scanf("%s", &component.label_of_TextBox);
        else if (component.type == 3)
            scanf("%s", &component.name_of_button);
    }
}

void is_details_valid() // For component details; Called in make_new_component funtion;
{
    if ((component.x + component.height) > 69)
    {
        printf("\n Error: Form index out of range:) (%d + %d) > 69 (maximum Heigth of From is 69);", component.x, component.height);
        make_new_component();
    }
    else if ((component.y + component.width) > 50)
    {
        printf("\n Error: Form index out of range:) (%d + %d) > 50 (maximum Width of From is 50);", component.y, component.width);
        make_new_component();
    }
}

void is_choosed_area_free() // Called in make_new_component function;
{
    int extra_homes = 0; // Number of homes should be empty after '-' characters (in corners of rigth side);
    int chooed_state = 0;
    int collision_founded = 0;
    int X = (component.x * 3);
    int Y = (component.y + 1);
    int Heigth = 0, Width = 0;

    if (component.type == 1 || component.type == 3)
    {
        Heigth = (component.height * 3);
        Width = component.width;
        if (component.type == 1)
            extra_homes = 1;
    }
    else if (component.type == 2)
        Heigth = strlen(component.name_of_lable);
    else if (component.type == 4)
        extra_homes = 1;

    for (int i = Y; i <= (Y + Width + extra_homes); i++)
    {
        for (int j = X; j <= (X + Heigth + extra_homes); j++)
        {
            if (Form.all_in_form[i][j] != ' ' || (Form.all_in_form[i][j] != ' ' && Form.all_in_form[i][j] != '\n'))
            {
                printf("\n Warning: some of homes in your choosed area are full;\n Do you want to continue << enter 0 >> or choose other area (other details) << enter 1 >> ? ");
                scanf("%d", &chooed_state);
                collision_founded = 1;
                break;
            }
        }

        if (collision_founded)
            break;
    }

    if (chooed_state)
    {
        if (runnin_mod.Edit)
            Edit_options();
        else
            make_new_component();
    }
}

// Component making functions (put components in FORM); .......................................................................................................

void put_TextBox()
{
    int X = (component.x * 3);
    int Y = (component.y + 1); // why +1? because the first row of all_in_form array is belong to the password (form password) :) ...
    int Width = component.width;
    int Heigth = (3 * component.height);
    int X2 = (X + Heigth + 1); // X of right side of TextBox;
    int Y2 = (Y + Width + 1);  // Y of buttom of TextBox;

    Form.all_in_form[Y][X] = '/';
    put_chars_with_a_word(1, 0, Heigth, '-', component.label_of_TextBox);
    Form.all_in_form[Y][X2] = '\\';

    put_chars_in_FormArr(0, X, Y, Width, '|'); // FormArr : all_in_form;
    put_chars_in_FormArr(0, X2, Y, Width, '|');

    Form.all_in_form[Y2][X] = '\\';
    put_chars_in_FormArr(1, X, (Y + Width + 1), Heigth, '-');
    Form.all_in_form[Y2][X2] = '/';
}

void put_lable()
{
    int X = (component.x * 3);
    int Y = (component.y + 1);
    int length_of_word = strlen(component.name_of_lable);
    put_words_in_FormArr(X, Y, length_of_word, component.name_of_lable);
}

void put_button()
{
    int X = (component.x * 3);
    int Y = (component.y + 1);
    int Width = component.width;
    int Heigth = (3 * component.height);
    int row_of_button_name = ((Width / 2) + 1);

    for (int i = 0; i < Width; i++)
    {
        if (i == (row_of_button_name - 1))
            put_chars_with_a_word(1, 1, Heigth, ':', component.name_of_button);
        else
            put_chars_in_FormArr(1, (X - 1), (Y + i), Heigth, ':');
    }
}

void put_CheckBox()
{
    int X = (component.x * 3);
    int Y = (component.y + 1);

    for (int i = 1; i <= component.num_of_CheckBox_options; i++)
    {
        Form.all_in_form[Y + 1][X] = '|'; // width == 1 (in all CheckBoxes);
        put_chars_in_FormArr(1, X, Y, 3, '-');
        put_chars_in_FormArr(1, X, (Y + 2), 3, '-');
        Form.all_in_form[Y + 1][X += 4] = '|';
        if (i < component.num_of_CheckBox_options)
        {
            Form.all_in_form[Y + 1][X += 1] = '|';
            Form.all_in_form[Y + 1][X++] = ' ';
        }
    }
}

// Other functions in part 1; .................................................................................................................................

void show_first_view() // called in show_view_and_command function
{
    for (int i = 0; i < 3; i++)
    {
        printf("\n |");
        if (i == 1)
            put_chars_with_a_word(0, 0, 205, ' ', "Point: here is View; the components will shown here! (in this CADR)");
        else
            put_character(' ', 205);
        putchar('|');
    }
}

void Free_the_Form() // To free the form arr (all_in_form arr) with putting white spaces in it;
{
    for (int i = 1; i <= 50; i++)
    {
        for (int j = 0; j < 207; j++)
            Form.all_in_form[i][j] = ' ';
    }
}

void make_new_component()
{
    if (!flag.are_inputs_entered)
    {
        if (!flag.stay_in_password_checking)
        {
            printf("\n\n At first, you sholud enter a password for your form;");
            printf("\n Maximum length for your password is 16 characters and minimum length is 4;");
            printf("\n Also your password should consist numbers, letters and characters;");
            printf("\n like ! - + ' and etc << without new lines or white spaces >>;");
            printf("\n Attention: Some characters are invalid; \\ / : < > ? * \" and |");
        }

        printf("\n Your password: ");
        scanf("%s", &Form.password);
        is_password_valid();
        system("cls");

        strcpy(Form.all_in_form[0], Form.password);
        printf("\n Now you can make your form with some components; Let's Go :)");
        enter_to_continue();
    }
    system("cls");

    printf("\n\n Attention: for Lable and CheckBox, you just enter x and y;");
    printf("\n Size of Lable just depond on length of it's name and for Checkbox considered a defult size by this program :);");
    printf("\n Note: for width of your Button, it's better to choose an Odd number (to have better style and shpae);");
    printf("\n Now you can enter your component type (TextBox: 1, Lable: 2, Button: 3, CheckBox: 4): ");
    scanf("%d", &component.type);

    if (component.type < 5 && component.type > 0)
    {
        printf("\n x: ");
        scanf("%d", &component.x);
        printf(" y: ");
        scanf("%d", &component.y);
    }
    if (component.type == 1 || component.type == 3)
    {
        printf(" width: ");
        scanf("%d", &component.width);
        printf(" height: ");
        scanf("%d", &component.height);
    }
    else if (component.type == 4)
    {
        printf("\n Please enter the number of CheckBox options: ");
        scanf("%d", &component.num_of_CheckBox_options);
        component.height = ((component.num_of_CheckBox_options * 2) + 1); // between boxes (boxes of CheckBox) we have an empty home (one home ~ one "-"); Note: ((+1) --> (-1 + 2);
        component.width = 1;
    }
    system("cls");

    flag.are_inputs_entered = 1;
    is_details_valid();     // When user doesn't pay attention to size and coordinate of FORM :) ;
    runnin_mod.Edit = 0;    // What? whit is it? this is used in phaze 3 (During the execution of the peogram); Why is it brought here? Because it used in is_choosed_area_free function;
    is_choosed_area_free(); // Gives a warning if this new component has Collision with past components;
    flag.show_command_options = 1;

    switch (component.type)
    {
    case 1:
        printf("\n Write a name as Lable of your TextBox\n Attention: this name is important; because it used during program execution; Ok?\n Write a name (without white sapces or new lines): ");
        scanf("%s", component.label_of_TextBox);
        is_name_valid(component.label_of_TextBox);
        put_TextBox(); // in Component making functions;
        break;
    case 2:
        printf("\n Write a name for your lable (without white sapces or new lines): ");
        scanf("%s", component.name_of_lable);
        put_lable();
        break;
    case 3:
        printf("\n Write a name for your button (without white sapces or new lines): ");
        scanf("%s", component.name_of_button);
        is_name_valid(component.name_of_button);
        put_button();
        break;
    case 4:
        printf("\n You can write a name for your checkbox with lables; So here you don't need to write any name:) ");
        put_CheckBox();
        enter_to_continue();
        break;
    default:
        make_new_component();
        break;
    }
    system("cls");

    show_view_and_command();
}

void command_options_part1()
{
    int choosed_state = 0;
    printf("\n\n Do you want to upload your form or continue making (with make a new component)? ");
    printf("\n\n ::::::::::::::::   ::::::::::::::::\
    \n :::: Upload ::::   ::: Make new :::\
    \n ::::::::::::::::   ::::::::::::::::\
    \n ___________________________________");

    printf("\n\n Attention: if you choose uploading, you can't continue making;\n So for editing your form or make new components in past forms, you need to load your saved form;");
    printf("\n To upload your maked form enter number 1 and for continue making enter 0: ");
    scanf("%d", &choosed_state);
    system("cls");

    flag.show_command_options = 0;
    show_view_and_command();
    if (choosed_state)
    {
        printf("\n\n ||||||||||||||||   ::::::::::::::::\
        \n |||| Upload ||||   ::: Make new :::\
        \n ||||||||||||||||   ::::::::::::::::\
        \n ___________________________________");
    }
    else
    {
        printf("\n\n ::::::::::::::::   ||||||||||||||||\
        \n :::: Upload ::::   ||| Make new |||\
        \n ::::::::::::::::   ||||||||||||||||\
        \n ___________________________________");

        putchar('\n');
        enter_to_continue();
        system("cls");

        make_new_component();
    }
}

// Part Two -------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Loading functions; .........................................................................................................................................

void load_in_form_arr(char pass_str[])
{
    char Character = 0;
    sprintf(pass_str, "%s.txt", Form.password);
    FILE *DF = fopen(pass_str, "r"); // DF: Data File;

    for (int i = 0; i <= 50; i++)
    {
        for (int j = 0; j < 207; j++)
        {
            Character = fgetc(DF);
            if (Character != ' ' && Character != '\n' && Character != '\t')
                Form.all_in_form[i][j] = Character;
        }
    }

    fclose(DF);
}

void load_created_form() // This function used in phaze 2 and 3 (part 1 and 2) but for easier to read the code, i writed it here;
{
    int choosed_state = 0;
    char password_arr[MaxLen]; // Password saved as file name (in uploading function); Which file? a text file that form saved in it;

    printf("\n Enter your password (without white spaces or new lines): ");
    scanf("%s", &Form.password);
    system("cls");

    if (is_password_exist(strlen(Form.password), Form.password))
    {
        load_in_form_arr(password_arr); // laoding created form in all_in_form array;
        flag.show_command_options = 1;
        show_view_and_command();
    }
    else
    {
        printf("\n This password was not found;\n Do you want to Enter another (enter 0) or create a new form (enter 1)? ");
        scanf("%d", &choosed_state);
        system("cls");

        if (choosed_state)
        {
            flag.are_inputs_entered = 0;
            run_flag.run_with_part1 = 1;
            run_flag.run_with_part2 = 0;
            run_flag.run_with_part1_load = 0;
            run_flag.run_with_part1_create = 1;
            make_new_component();
        }
        else
            load_created_form();
    }
}

// START of --| RUNNING the Form |-- functions (by using 5 types of bottuns);

// SUB-running_bottun functions; ......................................................................................................................................

// sub function for EDIT button;

void write_something_in_form(int Y, int X)
{
    char new_word[MaxLen];
    scanf("%s", new_word);

    // Following operands are for checking choosed area for entered word (in is_choosed_area_free function);
    component.x = (X / 3);
    component.y = (Y - 1);
    component.width = 1;
    component.height = strlen(new_word);

    system("cls");
    is_choosed_area_free();
    system("cls");

    for (int i = 0; new_word[i] != '\0'; i++)
        Form.all_in_form[Y][X++] = new_word[i];
}

// Running_button functions; .........................................................................................................................................

void Add_options()
{
    runnin_mod.Add = 1;

    printf("\n\n ||||||||||||||\
        \n |||| Add. ||||\
        \n ||||||||||||||\
        \n ______________\n");
    enter_to_continue();
}

void Find_options()
{
    char wanted_name[MaxLen2];
    runnin_mod.Add = 0;
    runnin_mod.Find = 1;
    runnin_mod.Edit = 0;
    runnin_mod.Remove = 0;
    runnin_mod.Update = 0;

    printf("\n\n ||||||||||||||\
        \n |||| Find ||||\
        \n ||||||||||||||\
        \n ______________\n");
    enter_to_continue();
    system("cls");

    flag.show_command_options = 1;
    show_view_and_command();
}

void Edit_options()
{
    int x = 0, y = 0;
    runnin_mod.Add = 0;
    runnin_mod.Edit = 1;
    runnin_mod.Find = 0;
    runnin_mod.Remove = 0;
    runnin_mod.Update = 0;

    printf("\n\n ||||||||||||||\
        \n |||| Edit ||||\
        \n ||||||||||||||\
        \n ______________\n");
    enter_to_continue();
    system("cls");

    printf("\n Please choose a home (with choosing it's coordinate) and write something there;");
    printf("\n X: ");
    scanf("%d", &x);
    printf(" Y: ");
    scanf("%d", &y);
    system("cls");

    printf("\n Write somthing in specified place;\n ----------------------------------");
    show_designed_form((y + 1), (3 * x)); // Why y+1? the form starts from index 1 of Form.all_in_form arr (Form.all_in_form[1][i]); So for put the from, we need to this summation (+1);
    put_character(' ', (3 * x) + 1);
    write_something_in_form((y + 1), (3 * x));
    system("cls");

    flag.show_command_options = 1;
    show_view_and_command();
}

void Remove_options()
{
    runnin_mod.Add = 0;
    runnin_mod.Edit = 0;
    runnin_mod.Find = 0;
    runnin_mod.Remove = 1;
    runnin_mod.Update = 0;
    int continue_removing = 0;

    printf("\n\n ||||||||||||||\
        \n ||| Remove |||\
        \n ||||||||||||||\
        \n ______________\n");
    enter_to_continue();

    printf("\n Are you sure to remove the shown form?");
    printf("\n To continue removing enter 1 and to stop this operation, enter 0: ");
    scanf("%d", &continue_removing);
    if (continue_removing)
        Free_the_Form();

    system("cls");
    flag.show_command_options = 1;
    show_view_and_command();
}

void Update_options()
{
    runnin_mod.Add = 0;
    runnin_mod.Find = 0;
    runnin_mod.Edit = 0;
    runnin_mod.Remove = 0;
    runnin_mod.Update = 1;

    printf("\n\n ||||||||||||||\
        \n ||| Update |||\
        \n ||||||||||||||\
        \n ______________\n");
    enter_to_continue();
    system("cls");

    flag.show_command_options = 1;
    show_view_and_command();
}

// Other functions in part 2 (About commands); ................................................................................................................

void first_command_descriptions()
{
    printf("\n\n Now you are allowed to run your form (or other designed forms);\n Here are 5 types of keys (buttons) that you can use them;");
    printf("\n\n ::::::::::::::   ::::::::::::::   ::::::::::::::   ::::::::::::::   ::::::::::::::\
    \n :::: Add. ::::   :::: Find ::::   :::: Edit ::::   ::: Remove :::   ::: Update :::\
    \n ::::::::::::::   ::::::::::::::   ::::::::::::::   ::::::::::::::   ::::::::::::::\
    \n __________________________________________________________________________________");

    printf("\n\n Add: to Add your form (like uploading) (By exiting command options);\n Find: to Find and show other designed forms;");
    printf("\n Edit: to Edit current form (a form that shown in view);\n Remove: to Remove current form;\n Update: to Save your last changes (after Editing or Removing) (By staying in command opptions);");

    printf("\n\n Options that now you can use them: 1.Add 2.Find 3.Edit 4.Remove (5.Update button, will be access after editing or removing forms);");
    printf("\n If you enter another number, you will exit this section and a form that shown in view, will be uploaded automatically; So be careful :);\n Your choosed option is: ");
}

void show_command_buttons_part2() // What does Part 2 mean? Part 2 of Project (that included phaze 3);
{
    if (runnin_mod.Add)
    {
        enter_to_continue();
    }
    else if (runnin_mod.Find)
    {
        printf("\n\n ::::::::::::::   ::::::::::::::   ::::::::::::::   ::::::::::::::\
        \n :::: Add. ::::   :::: Edit ::::   ::: Remove :::   ::: Update :::\
        \n ::::::::::::::   ::::::::::::::   ::::::::::::::   ::::::::::::::\
        \n _________________________________________________________________\n");
        printf("\n Choose one (Add: number 1, Edit: number 3, Remove: number 4): ");
    }
    else if (runnin_mod.Edit)
    {
        printf("\n ::::::::::::::   ::::::::::::::   ::::::::::::::\
        \n :::: Add. ::::   :::: Edit ::::   ::: Update :::\
        \n ::::::::::::::   ::::::::::::::   ::::::::::::::\
        \n ________________________________________________\n");
        printf("\n Choose one (Add: number 1, Edit: number 3, Upload: number 5): ");
    }
    else if (runnin_mod.Remove)
    {
        printf("\n ::::::::::::::   ::::::::::::::\
        \n :::: Add. ::::   ::: Update :::\
        \n ::::::::::::::   ::::::::::::::\
        \n _______________________________\n");
        printf("\n Choose one (Add: number 1, Update: number 5): ");
    }
    else if (runnin_mod.Update)
    {
        printf("\n ::::::::::::::   ::::::::::::::   ::::::::::::::   ::::::::::::::\
        \n :::: Add. ::::   :::: Find ::::   :::: Edit ::::   ::: Remove :::\
        \n ::::::::::::::   ::::::::::::::   ::::::::::::::   ::::::::::::::\
        \n ________________________________________________\n");
        printf("\n Choose one (Add: number 1, Find: number 2, Edit: number 3, Remove: number 4): ");
    }
}

void command_options_part2()
{
    int choosed_option = 0;
    if (flag.first_command_descriptions_part2)
        first_command_descriptions();
    else
        show_command_buttons_part2();

    scanf("%d", &choosed_option);
    system("cls");

    flag.first_command_descriptions_part2 = 0;
    flag.show_command_options = 0;
    show_view_and_command();

    switch (choosed_option)
    {
    case 1:
        Add_options();
        break;
    case 2:
        Find_options();
        break;
    case 3:
        Edit_options();
        break;
    case 4:
        Remove_options();
        break;
    case 5:
        Update_options();
        break;
    default:
        break;
    }

    system("cls");
}

// Functions that used in more than one phaze ----------------------------------------------------------------------------------------------------------------------------------------

// Sequenced by calling in main funciton (or other functions);

void create_or_load()
{
    int choosed_part = 0;
    printf("\n Do you want to create a form or load created forms? (to creating enter 0 and for loading enter 1): ");
    scanf("%d", &choosed_part);
    system("cls");

    if (choosed_part)
    {
        run_flag.run_with_part1_create = 0;
        printf("\n Do you want to load an empty form (just with components) (enter 0) or fulled form (Running a form) (enter 1)? ");
        scanf("%d", &choosed_part);
        if (choosed_part)
        {
            run_flag.run_with_part2 = 1;
            run_flag.run_with_part1 = 0;
            run_flag.run_with_part1_load = 0;
        }
        else
        {
            run_flag.run_with_part1_load = 1;
            run_flag.run_with_part1 = 1;
            run_flag.run_with_part2 = 0;
        }
    }
    else
    {
        run_flag.run_with_part2 = 0;
        run_flag.run_with_part1 = 1;
        run_flag.run_with_part1_load = 0;
        run_flag.run_with_part1_create = 1;
    }
    system("cls");
}

void basic_descriptions()
{
    system("cls");
    printf("\n\n");
    put_chars_with_a_word(0, 0, 207, '-', "| IN THE NAME OF ALLAH |");
    printf("\n\n Hello my dear;");
    create_or_load();

    if (run_flag.run_with_part1_load || run_flag.run_with_part2)
        printf("\n Welcome back; Please read the fllowing sentences just for reminding :);");
    else if (run_flag.run_with_part1_create)
        printf("\n << Very important >> Please read the following sentences to have a good design :)");

    if (run_flag.run_with_part1)
    {
        printf("\n Attention: This sentences are for all components; (TextBox, ComboBox and etc ... )\n");
        printf("\n Note 1: You should enter your considered coordinate with choosing x and y;");
        printf("\n Note 2: As you know, your table has a width and a height; You should choose them after choosing x and y;");
        printf("\n Note 3: in view, per << | >> considered as a << row >> (( one row == one width ))\n Also per << --- >> considered as a << column >> (( one column == one height ));");
        printf("\n Attention: For Button (one of types of components), per << ::: >> considered as a << column >>;");
        printf("\n Note 4: To create a TextBox: enter number 1 and for button: enter 2 ( Lable is choosed with the TextBox :);\n");
        printf("\n Note 5: About size and coordinate:\n Maximum size of FORM << not Component >>: heigth = 69 homes (index: 0 - 68) (include: 207 characters) and width = 50 homes (index: 0 - 49) (include: 50 characters);");
        printf("\n Be careful; the text above is about size of form (not components) ...\n So sum of sizes and coordinates of componentes that you will consider, must be less;");
        printf("\n For example: if x == 25, the maximum height of your component should be 43 (68 - 25);\n");
    }
    else
    {
        printf("\n\n Attention: If you maked a form in the past, now you can running your maked form;\n After loading your form, you can run it;");
        printf("\n\n Note 1: After running form, you can use 5 types of keys (buttons); 1.Add 2.Find 3.Edit 4.Remove 5.Update (Ok);");
        printf("\n Note 2: If you choose removing button, your shown form will be cleared; But your password won't be removed; ");
        printf("\n Why? becuse you maked a form in the past and This program must recognizes you as a form designer :)");
        printf("\n You can load your empty (removed) form and run in; (to edit it or etc ...);");
    }

    enter_to_continue();
    system("cls");
}

void show_designed_form(int y, int x) // show view with the components;
{
    putchar('\n');
    for (int i = 1; i <= y; i++)
    {
        putchar(' ');
        for (int j = 0; j < x; j++)
            putchar(Form.all_in_form[i][j]);
        putchar('\n');
    }
}

void show_view_and_command()
{
    printf("\n ");
    put_chars_with_a_word(0, 0, 207, '-', "View");

    if (flag.are_inputs_entered == 1)
        show_designed_form(50, 207);
    else
        show_first_view();

    printf("\n ");
    put_character('-', 207);
    printf("\n ");

    put_chars_with_a_word(0, 0, 207, '-', "Commands");
    if (flag.show_command_options == 1)
    {
        if (run_flag.run_with_part1)
            command_options_part1();
        else if (run_flag.run_with_part2)
            command_options_part2();
    }
}

void create_or_load_a_form()
{
    flag.are_inputs_entered = 1;
    flag.stay_in_password_checking = 0;
    Free_the_Form(); // To free the form arr (all_in_form arr) with putting white spaces in it;

    if (run_flag.run_with_part1_create)
    {
        flag.are_inputs_entered = 0;
        make_new_component(); // Creating a component; (phaze 1)
    }
    else
    {
        flag.first_command_descriptions_part2 = 1;
        load_created_form(); // loading a fulled form; (phaze 2 and 3 but this function writed in part 2)
    }

    upload_designed_form();
}

void upload_designed_form()
{
    if (run_flag.run_with_part1_create)
    {
        FILE *pf = fopen("passwords.txt", "a+"); // pf: passwords file;
        fputs(Form.password, pf);
        fputc('/', pf);
        fclose(pf);
    }

    char file_name[MaxLen];
    sprintf(file_name, "%s.txt", Form.password);
    FILE *df = fopen(file_name, "w"); // df: Data file (included Form);

    for (int i = 0; i <= 50; i++)
    {
        for (int j = 0; j < 207; j++)
            fputc(Form.all_in_form[i][j], df);
    }
    fclose(df);
}

void last_descriptions() // Good Bye Party :);
{
    int choosed_state = 0;
    printf("\n\n Your designed form, successfully uploaded;\n To see your designed form or create other forms, you must Sign in again;");
    printf("\n Do you have another request? (if you want to continue enter 1 but if you want to close the program enter 0)");
    printf("\n Your choise: ");
    scanf("%d", &choosed_state);
    system("cls");

    if (choosed_state)
    {
        create_or_load();
        create_or_load_a_form();
        last_descriptions();
    }
    else
        printf("\n Thaks for choosing us;\n We hope to see you again;\n Good Luck! :);\n");
}

// Main function --------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    basic_descriptions();
    show_view_and_command(); // To show first view
    create_or_load_a_form();
    last_descriptions();
    return 0;
}