# include "all_functions.h"

void displayRules() {
    FILE *file = fopen("how_to_play.html", "w"); // Create a new HTML file
    
    if (file == NULL) {
        printf("Error creating file!\n");
        return 1;
    }

    // Write HTML content to the file
    fprintf(file, "<!DOCTYPE html>\n");
    fprintf(file, "<html lang=\"en\">\n");
    fprintf(file, "<head>\n");
    fprintf(file, "    <meta charset=\"UTF-8\">\n");
    fprintf(file, "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    fprintf(file, "    <title>Game Rules</title>\n");
    fprintf(file, "    <link rel=\"icon\" href=\"/images/hangman.webp\" type=\"image/png\">\n");
    fprintf(file, "    <style>\n");
    fprintf(file, "        body {\n");
    fprintf(file, "            background-image: url('/images/background.png') !important;\n");
    fprintf(file, "            font-family: Arial, sans-serif;\n");
    fprintf(file, "            background-size: cover;\n");
    fprintf(file, "            background-size: 99%; /* Adjust the percentages as needed */\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        .Introduction,\n");
    fprintf(file, "        .General_Rules,\n");
    fprintf(file, "        .Have_Fun {\n");
    fprintf(file, "            margin: 0 auto; /* Center the content */\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        .Introduction {\n");
    fprintf(file, "            background-color: #000000;\n");
    fprintf(file, "            padding: 10px;\n");
    fprintf(file, "            text-align: center;\n");
    fprintf(file, "            color: #ffffff;\n");
    fprintf(file, "            width: 60%;\n");
    fprintf(file, "            margin-bottom: 10px;\n");
    fprintf(file, "        }\n");
    fprintf(file, "        .General_Rules {\n");
    fprintf(file, "            background-color: #000000;\n");
    fprintf(file, "            padding: 10px;\n");
    fprintf(file, "            text-align: center;\n");
    fprintf(file, "            color: #ffffff;\n");
    fprintf(file, "            width: 60%;\n");
    fprintf(file, "            margin-bottom: 10px;\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        .Have_Fun {\n");
    fprintf(file, "            margin-top: 10px;\n");
    fprintf(file, "            background-color: #000000;\n");
    fprintf(file, "            padding: 10px;\n");
    fprintf(file, "            text-align: center;\n");
    fprintf(file, "            color: #ffffff;\n");
    fprintf(file, "            width: 75%;\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        h1 {\n");
    fprintf(file, "            text-align: center;\n");
    fprintf(file, "            color: #ffffff;\n");
    fprintf(file, "            background-color: #000000;\n");
    fprintf(file, "            width: 61.5%;\n");
    fprintf(file, "            padding-top: 20px;\n");
    fprintf(file, "            padding-bottom: 20px;\n");
    fprintf(file, "            margin-left: 270px !important;\n");
    fprintf(file, "            animation: changeColor 3s infinite;\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        @keyframes changeColor {\n");
    fprintf(file, "            0% { color: red; }\n");
    fprintf(file, "            25% { color: green; }\n");
    fprintf(file, "            50% { color: blue; }\n");
    fprintf(file, "            75% { color: yellow; }\n");
    fprintf(file, "            100% { color: orange; }\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        /* Style the buttons that are used to open and close the accordion panel */\n");
    fprintf(file, "        .accordion {\n");
    fprintf(file, "            background-color: black;\n");
    fprintf(file, "            color: white;\n");
    fprintf(file, "            cursor: pointer;\n");
    fprintf(file, "            padding: 18px;\n");
    fprintf(file, "            width: 61.35%;\n");
    fprintf(file, "            text-align: left;\n");
    fprintf(file, "            border: none;\n");
    fprintf(file, "            outline: none;\n");
    fprintf(file, "            transition: 0.4s;\n");
    fprintf(file, "            margin-left: 274px !important;\n");
    fprintf(file, "            margin-bottom: 2px;\n");
    fprintf(file, "            font-size: medium;\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        /* Add a background color to the button if it is clicked on (add the .active class with JS), and when you move the mouse over it (hover) */\n");
    fprintf(file, "        .active, .accordion:hover {\n");
    fprintf(file, "            background-color: #ccc;\n");
    fprintf(file, "            color:#000000;\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        /* Style the accordion panel. Note: hidden by default */\n");
    fprintf(file, "        .panel {\n");
    fprintf(file, "            padding: 0 18px;\n");
    fprintf(file, "            background-color: white;\n");
    fprintf(file, "            max-height: 0;\n");
    fprintf(file, "            overflow: hidden;\n");
    fprintf(file, "            transition: max-height 0.2s ease-out;\n");
    fprintf(file, "            width: 58.8%;\n");
    fprintf(file, "            margin-left: 274px !important;\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        .accordion:after {\n");
    fprintf(file, "            content: '\\2304'; /* Unicode character for \"plus\" sign (+) */\n");
    fprintf(file, "            font-size: 13px;\n");
    fprintf(file, "            color: #777;\n");
    fprintf(file, "            float: right;\n");
    fprintf(file, "            margin-left: 5px;\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        .active:after {\n");
    fprintf(file, "            content: \"\\2038\"; /* Unicode character for \"minus\" sign (-) */\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        p {\n");
    fprintf(file, "            text-align: left;\n");
    fprintf(file, "            padding: 10px;\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        h2 {\n");
    fprintf(file, "            text-align: left;\n");
    fprintf(file, "            padding-left: 10px;\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "    </style>\n");
    fprintf(file, "</head>\n");
    fprintf(file, "<body>\n");
    fprintf(file, "        <h1>HANGMAN GAME RULES</h1>\n");
    fprintf(file, "        <div class=\"Introduction\">\n");
    fprintf(file, "            <h2>Introduction</h2>\n");
    fprintf(file, "            <p>Welcome to the text-based Hangman Game! Dive into word-cracking fun, but first, get familiar with our Game Rule Guide for an overview of what's in store!</p>\n");
    fprintf(file, "        </div>\n");
    fprintf(file, "\n");
    fprintf(file, "        <div class=\"General_Rules\">\n");
    fprintf(file, "           <h2>General Rule</h2> \n");
    fprintf(file, "           <p>This section covers the general rules applicable to the different modes of the game. Here they are: <br> <br> <br> 1. For every word you are trying to solve, you have 7 chances (7 lives). If you fail to solve the word after the 7 chances, the game terminates. <br><br> 2. You can either: guess a letter once at a time or try guessing the word all at once. <br><br> 3. You will get hints that will guide you to solving the word. <br><br> 4. You can exit and save your game at any point using the letter 'E'. <br><br> 5. They are 6 modes that you can choose to explore: Easy, Medium, Hard, Time Attack, Endless and Multiplayer. More details about them below! <br><br> 6. For all the modes, if you beat them, you get to input your own word to be solved. The word length should be greater than 3 letters. <br><br> 7. You also get revealed a cheat code randomly upon winning any mode, which will ease your playing experience.</p>\n");
    fprintf(file, "        </div>\n");
    fprintf(file, "\n");
    fprintf(file, "        <button class=\"accordion\">Easy Mode</button>\n");
    fprintf(file, "        <div class=\"panel\">\n");
    fprintf(file, "            <p>There are 20 levels on Easy Mode and the word length ranges between 4 and 5 letters. The 7 lives rule is applicable. If you finish with one of the top scores, it will be added to our Leaderboard!</p>\n");
    fprintf(file, "        </div>\n");
    fprintf(file, "\n");
    fprintf(file, "        <button class=\"accordion\">Medium Mode</button>\n");
    fprintf(file, "        <div class=\"panel\">\n");
    fprintf(file, "            <p>There are 20 levels on Medium Mode and the word length ranges between 4 and 6 letters. The 7 lives rule is applicable. If you finish with one of the top scores, it will be added to our Leaderboard!.</p>\n");
    fprintf(file, "        </div>\n");
    fprintf(file, "\n");
    fprintf(file, "        <button class=\"accordion\">Hard Mode</button>\n");
    fprintf(file, "        <div class=\"panel\">\n");
    fprintf(file, "            <p>There are 20 levels on Hard Mode and the word length ranges between 6 and 7 letters. The 7 lives rule is applicable. Each time you guess wrongly, you lose 1 point. If you manage to guess the word with 120 seconds (2 minutes), you earn an extra point. If you finish with one of the top scores, it will be added to our Leaderboard!</p>\n");
    fprintf(file, "        </div>\n");
    fprintf(file, "\n");
    fprintf(file, "        <button class=\"accordion\">Time Attack Mode</button>\n");
    fprintf(file, "        <div class=\"panel\">\n");
    fprintf(file, "            <p>In the time attack, you get to experience the countdown difficulty of Hard Mode and try to solve one word within 4 minutes. The word can be of any length between 4 to 7 letters. The 7 lives rule is applicable. If you manage to solve the game in 360 seconds (6 min), you win the round.</p>\n");
    fprintf(file, "        </div>\n");
    fprintf(file, "\n");
    fprintf(file, "        <button class=\"accordion\">Endless Mode</button>\n");
    fprintf(file, "        <div class=\"panel\">\n");
    fprintf(file, "            <p>There are unlimited tries and levels! You get to play words inputted by winners of other modes and play around without any constraints.</p>\n");
    fprintf(file, "        </div>\n");
    fprintf(file, "\n");
    fprintf(file, "        <button class=\"accordion\">Multiplayer Mode</button>\n");
    fprintf(file, "        <div class=\"panel\">\n");
    fprintf(file, "            <p>You get to play 20 levels consisting with words of word length 4-6 with a friend! You each have 7 lives and get to guess the word. If Player 1 fails to guess on the first try, for example, Player 2 gets to play.</p>\n");
    fprintf(file, "        </div>\n");
    fprintf(file, "\n");
    fprintf(file, "        <div class=\"Have_Fun\">Hope you have a fun time!</div>\n");
    fprintf(file, "\n");
    fprintf(file, "    <script>\n");
    fprintf(file, "        var acc = document.getElementsByClassName(\"accordion\");\n");
    fprintf(file, "        var i;\n");
    fprintf(file, "\n");
    fprintf(file, "        for (i = 0; i < acc.length; i++) {\n");
    fprintf(file, "            acc[i].addEventListener(\"click\", function() {\n");
    fprintf(file, "                this.classList.toggle(\"active\");\n");
    fprintf(file, "                var panel = this.nextElementSibling;\n");
    fprintf(file, "                if (panel.style.maxHeight) {\n");
    fprintf(file, "                  panel.style.maxHeight = null;\n");
    fprintf(file, "                } else {\n");
    fprintf(file, "                  panel.style.maxHeight = panel.scrollHeight + \"px\";\n");
    fprintf(file, "                }\n");
    fprintf(file, "            });\n");
    fprintf(file, "        }\n");
    fprintf(file, "    </script>\n");
    fprintf(file, "</body>\n");
    fprintf(file, "</html>\n");


    fclose(file); // Close the file

    // Open the generated HTML file in the default web browser
    system("xdg-open how_to_play.html"); // For Linux-based systems
}

int main() {
    displayRules();
    return 0;
}
