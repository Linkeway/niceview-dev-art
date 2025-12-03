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
# urchin.conf
CONFIG_CUSTOM_ANIMATION_SPEED=300000 # 300 second total duration
# 30 pictures, so 10 seconds per picture
```

## Adding new arts
1. Generate new PNG file and save it to `assets/` folder. When uisng AI, ask it to generate with a resolution of 68x140. This will help you better evaluate the final look on the display.
1. Use the command to convert the PNG to C code
   ```bash
   ./convert_png_to_c_code.sh assets/<art_name>.png
   ```
1. Now check the resulting C code under `boards/shields/nice_view/widgets/arts/<art name>.c`, find `<art name>_map[] = {` and replace the two color index lines with the following copied from the "mountain" or "balloon" images where "<art name>" is the name you put into the Image Converter:
    ```c
    #if CONFIG_NICE_VIEW_WIDGET_INVERTED
            0xff, 0xff, 0xff, 0xff, /*Color of index 0*/
            0x00, 0x00, 0x00, 0xff, /*Color of index 1*/
    #else
            0x00, 0x00, 0x00, 0xff, /*Color of index 0*/
            0xff, 0xff, 0xff, 0xff, /*Color of index 1*/
    #endif
    ```
1. Open the file `boards/shields/nice_view/widgets/peripheral_status.c` and add a line for your new art like `LV_IMG_DECLARE(<art name>);` near the top. Optionally, adding it as the first item in the array so that it shows up first when keyboard is reset.
1. In the same file, add a line  `&<art_name>,` after `const lv_img_dsc_t *anim_imgs[] = {`
1. In the same file, increment the number of images by one for the line `lv_animimg_set_src(art, (const void **) anim_imgs, <image number>);`
1. In `boards/shields/nice_view_custom/CMakeLists.txt`, add a line to tell the build system to include your new source file. Add the following line alongside the other zephyr_library_sources directives for the widgets: `zephyr_library_sources(widgets/arts/<art name>.c)` after the `zephyr_library_sources(widgets/art.c)` line.


