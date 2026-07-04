function res = check_note_validation(KeyEnergy, key)
    % 根据一个音符最强音的12和19个半音的强度来判断音符的可能性

    try
        energy_0 = KeyEnergy(key);
        energy_12 = KeyEnergy(key + 12);
        energy_19 = KeyEnergy(key + 19);
    catch
        res = 0;
        return;
    end

    wei = [0.15 1.2 0.4];

    res = wei * [energy_0 energy_12 energy_19]';

end
