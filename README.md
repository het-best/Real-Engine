<header>
  <div id="header" align="center">
    <h1> Open source game engine by HetBest. </h1>
    <h1> Sourses: </h1>
      <p> SFML </p>
    <h1> How to use? </h1>
      <p> You need to install SFML. </p>
      <p> If you want to release your game you need to add to game folder sfml-window-d-2.dll, sfml-system-d-2.dll and sfml-graphics-d-2.dll.  </p>
      <p> If you use network or audio you need add sfml-network-d-2.dll or sfml-audio-d-2.dll and openal32.dll. </p>
      <p> To use music, sounds or fonts add they to game folder. </p>
      <p> To use any symbols except english use "L" before string, example L"ąęتشшы". </p>
    <h1> Game functions </h1>
      <p> log_add(name of your log) - print your log add console, helps detect errors. </p>
      <p> set_cursor_visible(true or false) - hides or shows the cursor. </p>
      <p> set_position(Vector2i position) - set window position. </p>
      <p> set_size(Vector2u size) - set window size. </p>
      <p> set_title(your name) - redact window name. </p>
      <p> draw_circle(sfml color, circle size, circle position) - draw circle. </p>
      <p> draw_text(text color, path to font, text, text size, text position, sf::Text::text type, sf::Text::text type) - draw text. </p>
      <p> draw_polygon(sfml color, polygon points, polygon position) - draw polygon. </p>
      <p> play_music(path to music) - play music, use sf::Thread thread(&play_music, path to music); thread.launch();. </p>
      <p> play_sound(path to sound) - play sound, use sf::Thread thread(&play_sound, path to sound); thread.launch();. </p>
  </div>
</header>
<main>

</main>
