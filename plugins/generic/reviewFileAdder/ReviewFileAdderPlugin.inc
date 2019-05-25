<?php

import('lib.pkp.classes.plugins.GenericPlugin');

class ReviewFileAdderPlugin extends GenericPlugin
{

//    function register($category, $path, $mainContextId = null) {
//        if (parent::register($category, $path, $mainContextId)) {
//            if ($this->getEnabled($mainContextId)) {
//                // Add new navigation items in the navigation block plugin
//                HookRegistry::register('Plugins::Blocks::Navigation::BrowseBy',array($this, 'addNavigationItem'));
//
//            }
//            return true;
//        }
//        return false;
//    }

    function getDisplayName()
    {
        return 'ReviewFileAdder';
    }

    function getDescription()
    {
        return 'Automatically inserts review form as a file';
    }


}