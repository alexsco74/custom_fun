<?php

/**
 * @file
 * Page callbacks for custom fun
 */

/*
 * Preprocess for theme_header_contact_block
 */
function template_preprocess_header_contact_block(&$vars) {
  //drupal_add_css(drupal_get_path('module', 'custom_fun'). '/custom_fun_vie.css');
  $delta = $vars['opt']['delta'];
  $fields = $vars['opt']['fields'];
  $wei_def = 0;
  $vars['build'] = array(
    '#prefix' => '<div class="custom-fun custom-fun-' . str_replace('_', '-', $delta) . '">',
    '#suffix' => '</div>',
  );
  foreach ($fields as $name => $field_set) {
    $wei_def++;
    $var_key = "custom_fun_{$delta}_{$name}";
    $var_wei_key = $var_key . '_wei';
    $wei = variable_get($var_wei_key, $wei_def);

    $vars['build']["{$name}_wr"] = array(
      '#prefix' => '<span class="custom-fan-' . $name . '-wr">',
      '#suffix' => '</span>',
      '#weight' => $wei,
    );

    if (isset($field_set['formatter'])) {
      switch ($field_set['formatter']) {
        case 'mail_link':
          $value = trim(variable_get($var_key, $field_set['default']));
          $vars['build']["{$name}_wr"][$name] = array(
            '#markup' => '<a href="mailto:' . $value . '">' . $value . '</a>',
          );
          break;
        case 'phone_link':
          $value = trim(variable_get($var_key, $field_set['default']));
          $value_tel = str_replace(array('(', ')', ' ', '-'), '', $value);
          $vars['build']["{$name}_wr"][$name] = array(
            '#markup' => '<a href="tel:' . $value_tel . '">' . $value . '</a>',
          );
          break;
      }
    }
    else {
      $mrk = variable_get($var_key, $field_set['default']);
      if (module_exists('csas_qf')) {
        $mrk = trim(str_replace('%callback', theme('csas_qf_tme'), $mrk));
      }
      else {
        $mrk = str_replace('%callback', '', $mrk);
      }
      if (!empty($mrk)) {
        $vars['build']["{$name}_wr"][$name] = array(
          '#markup' => $mrk,
        );
      }
      else {
        $vars['build']["{$name}_wr"]['#access'] = FALSE;
      }
    }
  }
}

/*
 * Implements theme
 */

function theme_header_contact_block($vars) {
  return drupal_render($vars['build']);
}