;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    .emacs                                             :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: mdelage <mdelage@student.42.fr>            +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2014/01/21 18:15:15 by mdelage           #+#    #+#              ;
;    Updated: 2014/03/12 12:53:13 by mdelage          ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

; Load general features files
(setq config_files "/usr/share/emacs/site-lisp/")
(setq load-path (append (list nil config_files) load-path))

(load "list.el")
(load "string.el")
(load "comments.el")
(load "header.el")

(require 'color-theme)
(color-theme-initialize)
(color-theme-standard)

; Set default emacs configuration
(set-language-environment "UTF-8")
(setq-default font-lock-global-modes t)

; Affiche le nombre de ligne et de colonne
(setq-default line-number-mode t
			column-number-mode t)

; Reglage des taulations
(setq-default tab-width 4)

; Reglage de l'indentation avec des tabulations
(setq-default indent-tabs-mode t)

; Definis le comportement de la touche DEL
(global-set-key (kbd "DEL") 'backward-delete-char)

; Reglage pour le mode c
(setq-default c-backspace-function 'backward-delete-char)
(setq-default c-basic-offset 4)
(setq-default c-default-style "linux")

; Reglage des pas d'indentation
(setq-default tab-stop-list '(4 8 12 16 20 24 28 32 36 40 44 48 52 56 60
                             64 68 72 76 80 84 88 92 96 100 104 108 112 116 120))

; Load user configuration
(if (file-exists-p "~/.myemacs") (load-file "~/.myemacs"))

;*******************************************************************************;
; Reglage de l'affichage du man
(custom-set-variables
 '(Man-frame-parameters (quote pushy))
 '(pc-selection-mode t))
(custom-set-faces
 )
