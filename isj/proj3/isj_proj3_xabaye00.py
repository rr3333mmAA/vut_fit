#!/usr/bin/env python3

# ukol za 2 body
def first_odd_or_even(numbers):
    """Returns 0 if there is the same number of even numbers and odd numbers
       in the input list of ints, or there are only odd or only even numbers.
       Returns the first odd number in the input list if the list has more even
       numbers.
       Returns the first even number in the input list if the list has more odd 
       numbers.

    >>> first_odd_or_even([2,4,2,3,6])
    3
    >>> first_odd_or_even([3,5,4])
    4
    >>> first_odd_or_even([2,4,3,5])
    0
    >>> first_odd_or_even([2,4])
    0
    >>> first_odd_or_even([3])
    0
    """

    even_numbers = []
    odd_numbers = []

    for number in numbers:
        if number % 2:
            even_numbers.append(number)
    for number in numbers:
        if not number % 2:
            odd_numbers.append(number)

    if len(even_numbers) < len(odd_numbers) and even_numbers:
        return even_numbers[0]
    elif len(odd_numbers) < len(even_numbers) and odd_numbers:
        return odd_numbers[0]
    else:
        return 0


# ukol za 3 body
def to_pilot_alpha(word):
    """Returns a list of pilot alpha codes corresponding to the input word

    >>> to_pilot_alpha('Smrz')
    ['Sierra', 'Mike', 'Romeo', 'Zulu']
    """

    pilot_alpha = ['Alfa', 'Bravo', 'Charlie', 'Delta', 'Echo', 'Foxtrot',
        'Golf', 'Hotel', 'India', 'Juliett', 'Kilo', 'Lima', 'Mike',
        'November', 'Oscar', 'Papa', 'Quebec', 'Romeo', 'Sierra', 'Tango',
        'Uniform', 'Victor', 'Whiskey', 'Xray', 'Yankee', 'Zulu']

    pilot_alpha_list = []

    for letter in word:
        pilot_alpha_list.extend(
            list(
                filter(lambda x: x[0]==letter.upper(), pilot_alpha)
            )
        )
     
    return pilot_alpha_list


if __name__ == "__main__":
    import doctest
    doctest.testmod()
