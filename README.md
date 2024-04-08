# Tokenizer
Acts as a normal tokenizer, but doesn't follow the normal pattern of parser calling tokenizer with query strings passed in. Parser will get called after Tokenizer is finished, this is done to make tokenizing thread safe and thereby run faster.
