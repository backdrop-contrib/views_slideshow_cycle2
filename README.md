# Views Slideshow Cycle 2

This module provides a jQuery Cycle2 slideshow plugin for Views Slideshow,
heavily based on Views Slideshow: Cycle (bundled with Views Slideshow).
Modifications have been made to interface with some basic options of Cycle2,
though a lot remains to be done. New options added to Cycle2's API during
its beta will be accounted for where possible.

Benefits to using Cycle2 over the original Cycle are that Cycle2 natively
handles responsive design and (with an optional plugin) swipe events
on capable devices.

## Status

This port is incomplete and is based on a sandbox project for Drupal,
see https://www.drupal.org/sandbox/BenYoung/1832338.
I have found it necessary to add into the view the class 'cycle-slideshow' to
a div surrounding the image files in order to get the images to cycle.

## Installation

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules.

- Download the Cycle 2 library from http://malsup.github.io/jquery.cycle2.js

- Place jquery.cycle2.js or its minified version inside the sites
  libraries folder e.g. libraries/jquery.cycle2

- Optionally, place jquery.cycle2.swipe.js inside the same folder.
  Other plugins will be supported in the future.


## Use

  When creating or editing a View using the Slideshow display mode,
  select the Cycle2 slideshow type in the display settings, under Slides.
  (The original Cycle slideshow type is not required.)


## License

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.
    
        
## Current Maintainer for Backdrop

Graham Oliver (github.com/Graham-72/)

## Credits

### Developer for Drupal:

- Ben Young



