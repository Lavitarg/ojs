<?php

import('lib.pkp.classes.plugins.GenericPlugin');

class ReviewFileAdderPlugin extends GenericPlugin
{

    function register($category, $path, $mainContextId = null) {
        if (parent::register($category, $path, $mainContextId)) {
            if ($this->getEnabled($mainContextId)) {

                HookRegistry::register('reviewerreviewstep3form::validate',array($this, 'addFileCallback'));

            }
            return true;
        }
        return false;
    }

    function addFileCallback($hookName, $args){
        error_log("Hook catched! Length: " . (count($args)));
        foreach ($args as $s) {
            error_log(gettype($s));
        }
        error_log(get_class($args[0]));
        try{
            $MyStep3Form = $args[0];
            $MyRequest = Application::get()->getRequest();
            $userV = 'reviewFormResponses';
            $MyStep3Form->setData($userV, $MyRequest->getUserVar($userV));

        }catch (Exception $e){
            error_log($e->getMessage());
        }
        error_log('started main part');
        $reviewAssignment = $MyStep3Form->getReviewAssignment();

        if ($reviewAssignment->getReviewFormId()) {
            error_log('passed line 39');
            $reviewFormResponseDao = DAORegistry::getDAO('ReviewFormResponseDAO');
            $reviewFormResponses = $MyStep3Form->getData('reviewFormResponses');
            if (is_array($reviewFormResponses)) foreach ($reviewFormResponses as $reviewFormElementId => $reviewFormResponseValue) {
                $reviewFormResponse = $reviewFormResponseDao->getReviewFormResponse($reviewAssignment->getId(), $reviewFormElementId);
                if (!isset($reviewFormResponse)) {
                    $reviewFormResponse = new ReviewFormResponse();
                    error_log("reviewFormResponse wasnt set!");
                }
                $reviewFormElementDao = DAORegistry::getDAO('ReviewFormElementDAO');
                $reviewFormElement = $reviewFormElementDao->getById($reviewFormElementId);
                $elementType = $reviewFormElement->getElementType();
                switch ($elementType) {
                    case REVIEW_FORM_ELEMENT_TYPE_SMALL_TEXT_FIELD:
                    case REVIEW_FORM_ELEMENT_TYPE_TEXT_FIELD:
                    case REVIEW_FORM_ELEMENT_TYPE_TEXTAREA:
                        $reviewFormResponse->setResponseType('string');
                        $reviewFormResponse->setValue($reviewFormResponseValue);
                        error_log("its a string!!!!!11111111111");
                        error_log($reviewFormResponseValue);
                        break;
                    case REVIEW_FORM_ELEMENT_TYPE_RADIO_BUTTONS:
                    case REVIEW_FORM_ELEMENT_TYPE_DROP_DOWN_BOX:
                        $reviewFormResponse->setResponseType('int');
                        $reviewFormResponse->setValue($reviewFormResponseValue);
                        error_log("its a dropdown!");
                        error_log(strval($reviewFormResponseValue));
                        break;
                    case REVIEW_FORM_ELEMENT_TYPE_CHECKBOXES:
                        $reviewFormResponse->setResponseType('object');
                        $reviewFormResponse->setValue($reviewFormResponseValue);
                        break;
                }
//                if ($reviewFormResponse->getReviewFormElementId() != null && $reviewFormResponse->getReviewId() != null) {
//                    //$reviewFormResponseDao->updateObject($reviewFormResponse);
//                } else {
//                    $reviewFormResponse->setReviewFormElementId($reviewFormElementId);
//                    $reviewFormResponse->setReviewId($reviewAssignment->getId());
//                    $reviewFormResponseDao->insertObject($reviewFormResponse);
//                }
            }else error_log("reviewFormResponses not an array!");
        }else error_log('no form');
//        error_log(gettype($myRequest->getUserVar($args[0])));
//        error_log((strval($myRequest->getUserVar($args[0]))));
//        error_log($myRequest->getUserVar($args[0]));



        return false;


    }

    function getDisplayName()
    {
        return 'ReviewFileAdder';
    }

    function getDescription()
    {
        return 'Automatically inserts review form as a file';
    }


}