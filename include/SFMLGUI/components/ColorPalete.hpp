namespace ColorPalete
{
    enum ColorsSet {
        Bright,
        Dark,
        HighContrast
    };

    enum components {
        inactive,
        onmouse,
        active,
        blocked,
        outline,
        halftransparrent,
        semitransparrent,
        font,
        checkbox_active,
        checkbox_inactive,
        checkbox_onmouse,
        checkbox_blocked
    };

    sf::Color bright_inactive_color(255,255,255, 255);
    sf::Color bright_onmouse_color(255,255,255, 128);
    sf::Color bright_active_color(255,255,255, 64);
    sf::Color bright_blocked_color(176,176,176);
    sf::Color bright_outline_color(0,0,0);
    sf::Color bright_halftransparrent_color(255,255,255, 128);
    sf::Color bright_semitransparrent_color(255,255,255, 200);
    sf::Color bright_font_color(0,0,0);
    sf::Color bright_checkbox_inactive_color(0,0,255, 255);
    sf::Color bright_checkbox_onmouse_color(0,0,255, 128);
    sf::Color bright_checkbox_active_color(0,0,255, 64);

    // Dark theme
    sf::Color dark_inactive_color(50, 50, 50, 255);        // Ciemny kolor tła dla nieaktywnych elementów
    sf::Color dark_onmouse_color(100, 100, 100, 128);      // Jaśniejszy kolor podczas najechania myszką
    sf::Color dark_active_color(150, 150, 150, 64);        // Aktywny, półprzezroczysty kolor
    sf::Color dark_blocked_color(100, 100, 100);           // Zablokowany element w odcieniu szarości
    sf::Color dark_outline_color(255, 255, 255);           // Biały obrys
    sf::Color dark_halftransparrent_color(50, 50, 50, 128);// Półprzezroczysty ciemny kolor
    sf::Color dark_semitransparrent_color(75, 75, 75, 200);// Lekko przezroczysty ciemny kolor
    sf::Color dark_font_color(255, 255, 255);              // Biała czcionka dla lepszej widoczności
    sf::Color dark_checkbox_inactive_color(0, 128, 255, 255);  // Jasnoniebieski checkbox w stanie nieaktywnym
    sf::Color dark_checkbox_onmouse_color(0, 128, 255, 128);   // Przezroczysty niebieski na hover
    sf::Color dark_checkbox_active_color(0, 128, 255, 64);    // Przezroczysty niebieski w stanie aktywnym

    // High contrast theme
    sf::Color contrast_inactive_color(0, 0, 0, 255);       // Głębokie czarne tło dla nieaktywnych elementów
    sf::Color contrast_onmouse_color(255, 255, 0, 255);    // Jasnożółty przy najechaniu myszką
    sf::Color contrast_active_color(0, 255, 0, 255);       // Jaskrawozielony aktywny element
    sf::Color contrast_blocked_color(128, 128, 128);       // Mocno szary dla zablokowanych elementów
    sf::Color contrast_outline_color(255, 255, 255);       // Wyraźny biały obrys
    sf::Color contrast_halftransparrent_color(0, 0, 0, 128);// Półprzezroczyste czarne tło
    sf::Color contrast_semitransparrent_color(255, 255, 255, 200);// Jasny, przezroczysty element
    sf::Color contrast_font_color(255, 255, 255);          // Biała czcionka
    sf::Color contrast_checkbox_inactive_color(255, 0, 0, 255);   // Czerwony checkbox w stanie nieaktywnym
    sf::Color contrast_checkbox_onmouse_color(255, 255, 0, 128);  // Żółty checkbox na hover
    sf::Color contrast_checkbox_active_color(0, 255, 0, 255);     // Zielony checkbox w stanie aktywnym


    std::map <int, std::map <int, sf::Color>> Palete = {
        {Bright,{
            {inactive, bright_inactive_color},
            {onmouse, bright_onmouse_color},
            {active, bright_active_color},
            {blocked, bright_blocked_color},
            {outline, bright_outline_color},
            {halftransparrent, bright_halftransparrent_color},
            {semitransparrent, bright_semitransparrent_color},
            {font, bright_font_color},
            {checkbox_inactive, bright_checkbox_inactive_color},
            {checkbox_onmouse, bright_checkbox_onmouse_color},
            {checkbox_active, bright_checkbox_active_color},
        }
        },
        {Dark,{
            {inactive, dark_inactive_color},
            {onmouse, dark_onmouse_color},
            {active, dark_active_color},
            {blocked, dark_blocked_color},
            {outline, dark_outline_color},
            {halftransparrent, dark_halftransparrent_color},
            {semitransparrent, dark_semitransparrent_color},
            {font, dark_font_color},
            {checkbox_inactive, dark_checkbox_inactive_color},
            {checkbox_onmouse, dark_checkbox_onmouse_color},
            {checkbox_active, dark_checkbox_active_color},
        }
        },
        {HighContrast,{
            {inactive, contrast_inactive_color},
            {onmouse, contrast_onmouse_color},
            {active, contrast_active_color},
            {blocked, contrast_blocked_color},
            {outline, contrast_outline_color},
            {halftransparrent, contrast_halftransparrent_color},
            {semitransparrent, contrast_semitransparrent_color},
            {font, contrast_font_color},
            {checkbox_inactive, contrast_checkbox_inactive_color},
            {checkbox_onmouse, contrast_checkbox_onmouse_color},
            {checkbox_active, contrast_checkbox_active_color},
        }
        }};
};