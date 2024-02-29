#include "../inc/challengeScreen.hpp"

using namespace Engine;

ChallengeScreen::ChallengeScreen(std::string screen_name,
                                 Challenge* new_challenge) {
  set_name(screen_name);
  challenge = new_challenge;
}

void ChallengeScreen::init() {
  init_map();
  init_player();
  init_textfield();
  init_compiler_objects();
  init_console();
  init_current_user();
  init_back_button();
  init_dialog_box();
  update_console_initial_info();
}

void ChallengeScreen::draw() {
  verify_programmable_object_status();
  show_dialog_box_to_next_map();
  for (auto object : objects) {
    object->draw();
  }
}

void ChallengeScreen::verify_programmable_object_status() {
  if (player_object->get_status() == "INITIAL_STATE") {
    if (console_status != "Inicializado") {
      update_console_initial_info();
    }
  } else if (player_object->get_status() == "RUNNING_COMMAND_LIST") {
    update_console_running_info();
  } else if (player_object->get_status() == "FINISHED_COMMAND_LIST") {
    if (map->verify_all_trail_checked()) {
      dialog_box->activate();
      timer->start();
    } else {
      map->reset_all_trail_checks();
    }
  }
}

void ChallengeScreen::set_player_sprite(std::string path) {
  player_sprite = path;
}

void ChallengeScreen::init_map() {
  if (!challenge->completed()) {
    map = challenge->get_actual_map();
    map->set_position(map_position);
    map->init();
    limits = map->get_limits();
    add_object(map);
  } else {
    Engine::Game& game = Engine::Game::get_instance();
    game.load_screen("select_robot");
  }
}

void ChallengeScreen::init_player() {
  std::pair<int, int> player_object_position;
  player_object_position = map->get_obj_initial_position();
  std::pair<int, int> player_object_size(32, 32);
  player_object = new ProgrammableObject(
      "player_object", player_object_position, player_object_size);
  player_object->set_sprite(player_sprite);
  player_object->set_limits(limits.first, limits.second);
  add_object(player_object);
}

void ChallengeScreen::init_textfield() {
  text_field = new TextField("textfield", text_field_position, 35, 40);
  text_field->set_font("./assets/fonts/larabiefont-rg.ttf", 15);
  text_field->set_font_color(0x00, 0x00, 0x00, 0x00);
  add_object_with_input(text_field);
}

void ChallengeScreen::init_compiler_objects() {
  AEPCompiler* compiler = new AEPCompiler();
  std::pair<int, int> button_size(100, 35);
  CompilerButton* button =
      new CompilerButton("button", compiler_button_position, button_size);
  button->set_sprites("./assets/sprites/buttons/button1.png",
                      "./assets/sprites/buttons/button2.png");
  button->set_compiler(compiler);
  button->set_programmable(player_object);
  button->set_text_field(text_field);
  button->activate();
  add_object_with_input(button);
}

void ChallengeScreen::init_console() {
  console =
      new Engine::Field("console", console_position, std::make_pair(572, 117));
  console->set_color(219, 166, 80, 0x00);
  console->set_bold(true);
  console->set_font("./assets/fonts/larabiefont-rg.ttf", 15);
  console->set_text_per_line("Desafio:", 0);
  console->set_text_per_line("Dica:", 1);
  console->set_text_per_line("Status:", 2);
  console->set_text_per_line("Campos Cobertos:", 3);
  add_object(console);
}

void ChallengeScreen::init_back_button() {
  ToScreenButton* back_button = new ToScreenButton(
      "back_button", back_button_position, std::make_pair(32, 32), true);
  back_button->set_sprites("./assets/sprites/buttons/back1.png",
                           "./assets/sprites/buttons/back2.png");
  back_button->set_screen_name("select_robot");
  back_button->activate();
  add_object_with_input(back_button);
}

void ChallengeScreen::init_current_user() {
  UsersManage& users_manage = UsersManage::get_instance();
  current_user = users_manage.get_current_user();
}

void ChallengeScreen::init_dialog_box() {
  dialog_box = new DialogBox("dialog-box-object", dialog_box_position,
                             std::make_pair(380, 110));
  dialog_box->set_color(179, 102, 0, 0);
  dialog_box->set_text("Percurso realizado com sucesso!",
                       std::make_pair(15, 15));
  add_object(dialog_box);
  dialog_box->set_icon("./assets/sprites/objects/medalha.png",
                       std::make_pair(165, 50), std::make_pair(32, 64));
}

void ChallengeScreen::show_dialog_box_to_next_map() {
  if (dialog_box->is_active()) {
    if (timer->get_ticks() / 1000.f > 3) {
      map->set_completed(true);
      map->free();
      if (current_user) {
        current_user->set_map_progress(challenge->get_title());
      } else {
        std::cout << "Current user not found!" << std::endl;
      }
      timer->stop();
      dialog_box->deactivate();
      load();
    }
  }
}

void ChallengeScreen::update_console_initial_info() {
  if (map && console) {
    map->reset_all_trail_checks();
    console->set_text_per_line("Desafio: " + map->get_name(), 0);
    console->set_text_per_line("Dica: " + map->get_text_info(), 1);
    console_status = "Inicializado";
    console->set_text_per_line("Status: " + console_status, 2);
    console->set_text_per_line(
        "Campos Cobertos: 0/" +
            std::to_string(map->get_all_checked_field_count()),
        3);
  } else {
    std::cout << "Map and console not found!" << std::endl;
  }
}

void ChallengeScreen::update_console_running_info() {
  if (console_status != "Executando comandos!") {
    console_status = "Executando comandos!";
    console->set_text_per_line("Status: " + console_status, 2);
  }
  if (check_checked_fields != map->get_checked_field_count()) {
    check_checked_fields = map->get_checked_field_count();
    char bar = '/';
    console->set_text_per_line(
        "Campos Cobertos: " + std::to_string(map->get_checked_field_count()) +
            bar + std::to_string(map->get_all_checked_field_count()),
        3);
  }
}