<?php

/**
 * Plugin defenition
 */
$plugin = array (
  'title' => t('Group hierarchy graph'),
  'description' => t('Display a graph of group hierachy starting from a given group'),
  'required context' => new ctools_context_required(t('Group'), 'entity:group'),
  'category' => t('Organic groups'),
);

function og_subgroups_group_hierarchy_graph_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context)) {
    return FALSE;
  }
  $block = new stdClass();
  $module = 'og_subgroups';
  $block->module = $module;
  $block->title = 'Group hierarchy graph';
    
  if (module_exists('graphapi')) {
    $group = $context->data;
    //$structure = array();
    $graph = graphapi_new_graph();
    
    og_subgroups_get_reverse_hierarchy_tree_perm(array($group->gid),'', NULL, $structure, $graph);
  
    $options = array(
      'width' => 400,
      'height' => 400,
      'item-width' => 50,
    );
    $block->content = graphapi_container($graph, $options);
  }
  // Set error message.
  else {
     $block->content = '<div>' . t('ERROR: This plugin require graph API in order to work properly') . '</div>';
  }
  
  return $block;
}

function og_subgroups_group_hierarchy_graph_content_type_edit_form($form, &$form_state) {
  // provide a blank form so we have a place to have context setting.
  return $form;
}
