# Nice!View Dev Arts
This is a zmk module to implement a slideshow of a collection of programming-themed 1 bit art on the peripheral (right) nice!view display.

NOTE: This is a fork off the beautiful [GPeye/hammerbeam-slideshow repo](https://github.com/GPeye/hammerbeam-slideshow) but replace the beautiful arts from Hammerbeam with my dev related pixel arts.

The picture to be displayed by this module on the peripheral screen will be one of these 30+ and will change every 10 seconds.

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

by default the this urchin animation will run for a duration of 300 seconds, 10 seconds per picture, fairly slow to save battery

If you want to change the speed of the animation, you can edit the speed by changing the CONFIG_CUSTOM_ANIMATION_SPEED in your .conf file

For example:

```conf
# your keyboard project's config/<your_project>.conf
CONFIG_CUSTOM_ANIMATION_SPEED=300000 # 300 second total duration
# 30 pictures, so 10 seconds per picture
```

If you want to disable specific images, you can set their corresponding configuration flags to `n` in your keyboard project's (not this repo) `config/<your_project>.conf` file.
The flags are named `CONFIG_CUSTOM_ART_<IMAGE_NAME>` where `<IMAGE_NAME>` is the uppercase version of the image name.
For example, to disable the `vim` and `hammerbeam1` images:

```conf
# your keyboard project's config/<your_project>.conf
CONFIG_CUSTOM_ART_VIM=n
CONFIG_CUSTOM_ART_HAMMERBEAM1=n
```

## Adding new arts
The workflow can be used as a playbook for AI execution.

1. Generate new PNG file and save it to `assets/` folder. When uisng AI, ask it to generate with a resolution of 68x140. This will help you better evaluate the final look on the display.
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
1. Open `boards/shields/nice_view_custom/Kconfig.defconfig` and add a new config entry for your art. For example:
    ```kconfig
    config CUSTOM_ART_<ART_NAME>
        bool "Show <art name> art"
        default y
    ```
    Remember to replace `<ART_NAME>` with the uppercase version of your art's name and `<art name>` with the regular name.
