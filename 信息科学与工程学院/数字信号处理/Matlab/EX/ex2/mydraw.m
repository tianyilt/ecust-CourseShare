function mydraw(n, b, a, x):
    y = signal.lfilter(b, a, x);
    plt.figure();
    plt.subplot(2, 2, 1);
    plt.plot(n, y);
    plt.title('y');
    z, p, k = signal.tf2zpk(b, a);
    plt.subplot(2, 2, 2);
    plt.plot(np.real(z), np.imag(z), 'o', np.real(p), np.imag(p), 'x');
    plt.title('z and p');
    w, Fh = signal.freqz(b, a);
    plt.subplot(2, 2, 3);
    plt.plot(w / np.pi, np.abs(Fh));
    plt.title('|H(w)|');
    plt.subplot(2, 2, 4);
    plt.plot(w / np.pi, np.angle(Fh));
    plt.title('ang|H(w)|');