<?php
/**
 * @file
 * Integration with the Views Slideshow module.
 */

/**
 * Implements hook_views_slideshow_slideshow_info().
 */
function views_slideshow_cycle2_views_slideshow_slideshow_info() {
  return array(
    'views_slideshow_cycle2' => array(
      'name' => t('Cycle2'),
      'accepts' => array(
        'goToSlide',
        'nextSlide',
        'pause',
        'play',
        'previousSlide',
      ),
      'calls' => array(
        'transitionBegin',
        'transitionEnd',
        'goToSlide',
        'nextSlide',
        'pause',
        'play',
        'previousSlide',
      ),
    ),
  );
}

/**
 * Implements hook_views_slideshow_slideshow_type_form().
 */
function views_slideshow_cycle2_views_slideshow_slideshow_type_form(&$form, &$form_state, &$view) {
  $default_values = $view->options['views_slideshow_cycle2'];

  // Transition settings.
  $form['views_slideshow_cycle2']['transition'] = array(
    '#markup' => '<h2>' . t('Transition') . '</h2>',
  );
  $form['views_slideshow_cycle2']['fx'] = array(
    '#type' => 'select',
    '#title' => t('Effect'),
    '#description' => t('The transition effect used to change slides.'),
    '#options' => array(
      'none' => 'None',
      'fade' => 'Fade',
      'fadeout' => 'Fade out',
      'scrollHorz' => 'Scroll (horizontal)',
      'scrollVert' => 'Scroll (vertical)',
      'carousel' => 'Carousel',
      'flipHorz' => 'Flip (horizontal)',
      'flipVert' => 'Flip (vertical)',
      'shuffle' => 'Shuffle',
      'tileSlide' => 'Tile (slide)',
      'tileBlind' => 'Tile (blinds)',
    ),
    '#default_value' => $default_values['fx'],
  );

  // Transition effect options.
  $form['views_slideshow_cycle2']['effect_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Effect options'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name$="[views_slideshow_cycle2][fx]"]' => array(
          array('value' => 'carousel'),
          array('value' => 'shuffle'),
          array('value' => 'tileSlide'),
          array('value' => 'tileBlind'),
        ),
      ),
    ),
  );
  // Carousel.
  $form['views_slideshow_cycle2']['effect_options']['carousel-vertical'] = array(
    '#type' => 'select',
    '#title' => t('Direction'),
    '#options' => array(
      'false' => t('Horizontal'),
      'true' => t('Vertical'),
    ),
    '#default_value' => $default_values['carousel-vertical'],
    '#states' => array(
      'visible' => array(
        ':input[name$="[views_slideshow_cycle2][fx]"]' => array('value' => 'carousel'),
      ),
    ),
  );
  $form['views_slideshow_cycle2']['effect_options']['carousel-visible'] = array(
    '#type' => 'number',
    '#title' => t('Number of slides'),
    '#description' => t("Number of slides to be displayed in the carousel. Leave empty to display as many slides as can fit in the slideshow container. Setting this option will cause the carousel to have a fixed width unless 'Responsive' is set below."),
    '#default_value' => $default_values['carousel-visible'],
    '#min' => 1,
    '#max' => 999,
    '#states' => array(
      'visible' => array(
        ':input[name$="[views_slideshow_cycle2][fx]"]' => array('value' => 'carousel'),
      ),
    ),
  );
  $form['views_slideshow_cycle2']['effect_options']['carousel-fluid'] = array(
    '#type' => 'checkbox',
    '#title' => t('Responsive'),
    '#description' => t("If this is enabled and 'Number of slides' is set, then the slides within the carousel will be resized in order to fill the container with the number of slides specified above."),
    '#default_value' => $default_values['carousel-fluid'],
    '#return_value' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name$="[views_slideshow_cycle2][fx]"]' => array('value' => 'carousel'),
        ':input[name$="[carousel-visible]"]' => array('!value' => ''),
      ),
    ),
  );
  // Shuffle.
  $form['views_slideshow_cycle2']['effect_options']['shuffle-left'] = array(
    '#type' => 'number',
    '#title' => t('Left position'),
    '#description' => t("Number of pixels relative to the container's left edge to move the slide when transitioning. Set to negative to move beyond the container's left edge."),
    '#default_value' => $default_values['shuffle-left'],
    '#min' => -9999,
    '#max' => 9999,
    '#states' => array(
      'visible' => array(
        ':input[name$="[views_slideshow_cycle2][fx]"]' => array('value' => 'shuffle'),
      ),
    ),
  );
  $form['views_slideshow_cycle2']['effect_options']['shuffle-right'] = array(
    '#type' => 'number',
    '#title' => t('Right position'),
    '#description' => t("Number of pixels relative to the container's right edge to move the slide when transitioning. Set to negative to move beyond the container's right edge. If 'Left position' is set above, this value will be ignored."),
    '#default_value' => $default_values['shuffle-right'],
    '#min' => -9999,
    '#max' => 9999,
    '#states' => array(
      'visible' => array(
        ':input[name$="[views_slideshow_cycle2][fx]"]' => array('value' => 'shuffle'),
      ),
    ),
  );
  $form['views_slideshow_cycle2']['effect_options']['shuffle-top'] = array(
    '#type' => 'number',
    '#title' => t('Vertical position'),
    '#description' => t("Number of pixels to shuffle in a vertical direction. A positive number indicates shuffling the slide downward and a negative number indicates shuffling upward."),
    '#default_value' => $default_values['shuffle-top'],
    '#min' => -9999,
    '#max' => 9999,
    '#states' => array(
      'visible' => array(
        ':input[name$="[views_slideshow_cycle2][fx]"]' => array('value' => 'shuffle'),
      ),
    ),
  );
  // Tile.
  $form['views_slideshow_cycle2']['effect_options']['tile-vertical'] = array(
    '#type' => 'select',
    '#title' => t('Direction'),
    '#options' => array(
      'true' => t('Vertical'),
      'false' => t('Horizontal'),
    ),
    '#default_value' => $default_values['tile-vertical'],
    '#states' => array(
      'visible' => array(
        ':input[name$="[views_slideshow_cycle2][fx]"]' => array(
          array('value' => 'tileSlide'),
          array('value' => 'tileBlind'),
        ),
      ),
    ),
  );
  $form['views_slideshow_cycle2']['effect_options']['tile-count'] = array(
    '#type' => 'number',
    '#title' => t('Tile count'),
    '#description' => t('The number of tiles to use in the transition.'),
    '#default_value' => $default_values['tile-count'],
    '#min' => 1,
    '#max' => 99,
    '#states' => array(
      'visible' => array(
        ':input[name$="[views_slideshow_cycle2][fx]"]' => array(
          array('value' => 'tileSlide'),
          array('value' => 'tileBlind'),
        ),
      ),
    ),
  );
  $form['views_slideshow_cycle2']['effect_options']['tile-delay'] = array(
    '#type' => 'number',
    '#title' => t('Tile delay'),
    '#description' => t('The number of milliseconds to delay each individual tile transition.'),
    '#default_value' => $default_values['tile-delay'],
    '#min' => 1,
    '#max' => 9999,
    '#states' => array(
      'visible' => array(
        ':input[name$="[views_slideshow_cycle2][fx]"]' => array(
          array('value' => 'tileSlide'),
          array('value' => 'tileBlind'),
        ),
      ),
    ),
  );

  $form['views_slideshow_cycle2']['timeout'] = array(
    '#type' => 'number',
    '#title' => t('Slide interval'),
    '#description' => t("Amount of time, in milliseconds, each slide is shown for. Set to '0' to disable the slideshow (slides must be transitioned manually)."),
    '#default_value' => $default_values['timeout'],
    '#min' => 0,
    '#max' => 99999,
  );
  $form['views_slideshow_cycle2']['speed'] = array(
    '#type' => 'number',
    '#title' => t('Transition speed'),
    '#description' => t('The speed, in milliseconds, of the transition effect.'),
    '#default_value' => $default_values['speed'],
    '#min' => 1,
    '#max' => 99999,
  );

  // Transition advanced options.
  $form['views_slideshow_cycle2']['transition_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Transition advanced options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['views_slideshow_cycle2']['transition_advanced']['delay'] = array(
    '#type' => 'number',
    '#title' => t('Initial delay'),
    '#description' => t("Amount of time, in milliseconds, to add onto or substract from the first slide's interval."),
    '#default_value' => $default_values['delay'],
    '#min' => 0,
    '#max' => 99999,
  );
  $form['views_slideshow_cycle2']['transition_advanced']['sync'] = array(
    '#type' => 'checkbox',
    '#title' => t('Synchronize transitions'),
    '#description' => t('When enabled, the transition effect of the incoming and outgoing slides will be synchronized. When disabled, the transition effect for the incoming slide will not start until the transition effect for the outgoing slide completes.'),
    '#default_value' => $default_values['sync'],
    '#return_value' => TRUE,
  );
  $form['views_slideshow_cycle2']['transition_advanced']['swipe'] = array(
    '#type' => 'checkbox',
    '#title' => t('Swipe gesture support'),
    '#description' => t('Enable swipe gesture support for advancing the slideshow forward or back on mobile devices.'),
    '#default_value' => $default_values['swipe'],
    '#return_value' => TRUE,
  );

  // Action settings.
  $form['views_slideshow_cycle2']['action'] = array(
    '#markup' => '<h2>' . t('Action') . '</h2>',
  );
  $form['views_slideshow_cycle2']['pause-on-hover'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pause on hover'),
    '#description' => t('Pause an auto-running slideshow while the mouse is over the slideshow.'),
    '#default_value' => $default_values['pause-on-hover'],
    '#return_value' => TRUE,
  );

  // Action advanced options.
  $form['views_slideshow_cycle2']['action_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Action advanced options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['views_slideshow_cycle2']['action_advanced']['allow-wrap'] = array(
    '#type' => 'checkbox',
    '#title' => t('Loop slideshow'),
    '#description' => t('When enabled, the slideshow will loop back to the first slide after showing the last one (and vice versa). When disabled, the slideshow will stop after the last slide.'),
    '#default_value' => $default_values['allow-wrap'],
    '#return_value' => TRUE,
  );
  $form['views_slideshow_cycle2']['action_advanced']['paused'] = array(
    '#type' => 'checkbox',
    '#title' => t('Begin paused'),
    '#description' => t('Begin the slideshow in a paused state.'),
    '#default_value' => $default_values['paused'],
    '#return_value' => TRUE,
  );
  $form['views_slideshow_cycle2']['action_advanced']['auto-height'] = array(
    '#type' => 'select',
    '#title' => t('Auto height'),
    '#description' => t("The method used to determine and manage the height of the slideshow.<br><strong>Disabled:</strong> Disable height management (use CSS to manually set the height of your slideshow).<br><strong>First slide:</strong> The height of the first slide determines the height of the slideshow.<br><strong>Tallest slide:</strong> The height of the tallest slide determines the height of the slideshow.<br><strong>Dynamic:</strong> The height of the slideshow changes depending on the height of the current slide."),
    '#options' => array(
      'false' => t('Disabled'),
      '0' => t('First slide'),
      'calc' => t('Tallest slide'),
      'container' => t('Dynamic'),
    ),
    '#default_value' => $default_values['auto-height'],
  );
  $form['views_slideshow_cycle2']['action_advanced']['loader'] = array(
    '#type' => 'select',
    '#title' => t('Image loader'),
    '#description' => t('Set the image loader behavior for the slideshow.<br><strong>Wait:</strong> Wait for all images to load before starting the slideshow.<br><strong>Quick:</strong> Show slides as individual images load. NOTE: Slides may appear out of order.'),
    '#options' => array(
      'false' => t('None'),
      'wait' => t('Wait'),
      'true' => t('Quick'),
    ),
    '#default_value' => $default_values['loader'],
  );
}

/**
 * Implements hook_views_slideshow_options_form_submit().
 */
function views_slideshow_cycle2_views_slideshow_options_form_submit($form, &$form_state) {
  $options = &$form_state['values']['style_options']['views_slideshow_cycle2'];

  // Flatten form values array.
  foreach ($options['effect_options'] as $key => $value) {
    $options[$key] = $value;
  }
  unset($options['effect_options']);
  foreach ($options['transition_advanced'] as $key => $value) {
    $options[$key] = $value;
  }
  unset($options['transition_advanced']);
  foreach ($options['action_advanced'] as $key => $value) {
    $options[$key] = $value;
  }
  unset($options['action_advanced']);

  // Convert boolean integers to TRUE/FALSE.
  $booleans = array('sync', 'swipe', 'pause-on-hover', 'allow-wrap', 'paused');
  foreach ($options as $key => &$value) {
    if (in_array($key, $booleans)) {
      $value = ($value) ? TRUE : FALSE;
    }
  }
}

/**
 * Implements hook_views_slideshow_option_definition().
 */
function views_slideshow_cycle2_views_slideshow_option_definition() {
  return array(
    'views_slideshow_cycle2' => array(
      'contains' => array(
        'fx' => array('default' => 'fade'),

        // Effect options.
        'carousel-vertical' => array('default' => 'false'),
        'carousel-visible' => array('default' => NULL),
        'carousel-fluid' => array('default' => FALSE),
        'shuffle-left' => array('default' => 0),
        'shuffle-right' => array('default' => 0),
        'shuffle-top' => array('default' => 15),
        'tile-vertical' => array('default' => 'true'),
        'tile-count' => array('default' => 7),
        'tile-delay' => array('default' => 100),

        // Transition.
        'timeout' => array('default' => 4000),
        'speed' => array('default' => 500),
        'delay' => array('default' => 0),
        'sync' => array('default' => TRUE),
        'swipe' => array('default' => FALSE),

        // Action.
        'pause-on-hover' => array('default' => FALSE),
        'allow-wrap' => array('default' => TRUE),
        'paused' => array('default' => FALSE),
        'auto-height' => array('default' => '0'),
        'loader' => array('default' => 'false'),
      ),
    ),
  );
}

