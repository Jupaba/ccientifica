<?php
#
# Markdown  -  A text-to-HTML conversion tool for web writers
#
# PHP Markdown
# Copyright (c) 2004-2015 Michel Fortin
# <https://michelf.ca/projects/php-markdown/>
#
# Original Markdown
# Copyright (c) 2004-2006 John Gruber
# <http://daringfireball.net/projects/markdown/>
#


#
# Markdown Parser Interface
#

interface MarkdownInterface {

  #
  # Initialize the parser and return the result of its transform method.
  # This will work fine for derived classes too.
  #
  public static function defaultTransform($text);

  #
  # Main function. Performs some preprocessing on the input text
  # and pass it through the document gamut.
  #
  public function transform($text);

}
