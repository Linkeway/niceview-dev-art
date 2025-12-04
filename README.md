# Nice!View Dev Arts

This ZMK module displays a slideshow of **programming-themed** 1-bit art on the peripheral (right-hand) nice!view display.
It offers a great balance between aesthetics and battery life, cycling through a collection of 30+ images at a configurable interval.

The repo is structured for easier adding and sharing new arts.
New art can be added to the repository for everyone to use, and _**each piece is individually configurable so you can curate your own collection in your keyboard project**_.
Contributions are welcome!
If you have an idea for new art, please open an issue.

![art](./assets/vim.png)

This project is a fork of the excellent [GPeye/hammerbeam-slideshow](https://github.com/GPeye/hammerbeam-slideshow), adding on top of the original Hammerbeam art with developer-focused pixel art.

## Usage

To use this module, first add it to your config/west.yml by adding a new entry to remotes and projects:

```yml
manifest:
  remotes:
      # zmk official
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
    - name: Linkeway                         #new entry
      url-base: https://github.com/Linkeway  #new entry
  projects:
    - name: zmk
      remote: zmkfirmware
      revision: main
      import: app/west.yml
    - name: niceview-dev-art                #new entry
      remote: Linkeway                      #new entry
      revision: main                        #new entry
  self:
    path: config
```

Now simply swap out the default nice_view shield on the board for the custom one in your build.yaml file.

```yml
---
include:
  - board: nice_nano_v2
    shield: urchin_left nice_view_adapter  nice_view
  - board: nice_nano_v2
    shield: urchin_right nice_view_adapter nice_view_custom #custom shield
```

By default, the full slideshow will run for a duration of 300 seconds (around 10 seconds per picture), which is slow to conserve battery life.
If you want to change the speed of the animation, you can edit the speed by changing the `CONFIG_CUSTOM_ANIMATION_SPEED` in your `.conf` file.

For example:
```conf
# your keyboard project's config/<your_project>.conf
CONFIG_CUSTOM_ANIMATION_SPEED=300000 # 300 second total duration for all arts
```

### Configuring Your Slideshow

This module operates in a "curator" mode by default to prevent firmware bloat. No art is included unless you explicitly enable it.

#### Curating Your Collection

To add specific art to your slideshow, enable it in your keyboard project's `config/<your_keyboard>.conf` file:

```conf
# I want to see these specific art pieces
CONFIG_CUSTOM_ART_VIM=y
CONFIG_CUSTOM_ART_HAMMERBEAM1=y
CONFIG_CUSTOM_ART_HAMMERBEAM2=y
```

#### Surprise Me: The Featured Art

If you enjoy surprises, you can have the single latest/featured art piece automatically included when you rebuild firmware. This is enabled by default via the `CONFIG_CUSTOM_ART_SURPRISE_ME` flag.

If you wish to disable this feature, add the following to your `.conf` file:
```conf
# Disable the featured art
CONFIG_CUSTOM_ART_SURPRISE_ME=n
```

If you don't like the *currently* featured art, you can also disable it specifically without turning off the feature for future art:
```conf
# I want featured art, but I don't like the 'vim' one
CONFIG_CUSTOM_ART_SURPRISE_ME=y
CONFIG_CUSTOM_ART_VIM=n 
```

## Adding new arts
The workflow can be used as a playbook for AI execution.

1. Generate new PNG file and save it to `assets/` folder. When using AI, ask it to generate with a resolution of 68x140. This will help you better evaluate the final look on the display.
1. Use the command to convert the PNG to C code
   ```bash
   ./convert_png_to_c_code.sh assets/<art_name>.png
   ```
1. Copy the printed out pixel array.
1. Use `boards/shields/nice_view/widgets/arts/art_name.c.template` as a template, create a new `boards/shields/nice_view/widgets/arts/<art name>.c`.
1. In the new .c file, replace the `<art_name>` with the actual art name; replace `<ART_NAME>` with the upper case name.
1. Paste the pixel array to the file.
1. In `boards/shields/nice_view_custom/widgets/peripheral_status.c`, add the following lines for your new art near the top. Remember to replace `<ART_NAME>` with the uppercase version of your art's name.
    ```c
    #if IS_ENABLED(CONFIG_CUSTOM_ART_<ART_NAME>)
    LV_IMG_DECLARE(<art_name>);
    #endif
    ```
1. In the same file, add the following lines after `const lv_img_dsc_t *anim_imgs[] = {`. Remember to replace `<ART_NAME>` with the uppercase version of your art's name. Optionally, adding it as the first item in the array so that it shows up first when keyboard is reset.
    ```c
    #if IS_ENABLED(CONFIG_CUSTOM_ART_<ART_NAME>)
    &<art_name>,
    #endif
    ```
1. Open `boards/shields/nice_view_custom/Kconfig.defconfig`. This repo uses a "Featured Art" system to avoid firmware bloat for users. When adding new art, you should make it the new featured piece.
    *   **Add the new art's config**, giving it the special `default y if CUSTOM_ART_SURPRISE_ME`.
    *   **Find the previous featured art** (the one with `default y if...`) and change its default to `n`.

    For example, if you are adding `neovim` and `vim` was the old featured art:
    ```kconfig
    # 1. Add the new art with the special default
    config CUSTOM_ART_NEOVIM
        bool "Show neovim art"
        default y if CUSTOM_ART_SURPRISE_ME
        default n

    # 2. Change the old featured art's default back to n
    config CUSTOM_ART_VIM
        bool "Show vim art"
        default n
    ```
